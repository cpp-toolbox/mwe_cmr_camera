#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics/draw_info/draw_info.hpp"
#include "input/glfw_lambda_callback_manager/glfw_lambda_callback_manager.hpp"
#include "input/input_state/input_state.hpp"

#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"
#include "utility/unique_id_generator/unique_id_generator.hpp"
#include "utility/print_utils/print_utils.hpp"

#include "graphics/catmull_rom_interpolator/catmull_rom_interpolator.hpp"
#include "graphics/scripted_transform/scripted_transform.hpp"
#include "graphics/vertex_geometry/vertex_geometry.hpp"
#include "graphics/shader_standard/shader_standard.hpp"
#include "graphics/batcher/generated/batcher.hpp"
#include "graphics/shader_cache/shader_cache.hpp"
#include "graphics/fps_camera/fps_camera.hpp"
#include "graphics/window/window.hpp"
#include "graphics/colors/colors.hpp"

#include <iostream>

int main() {
    Colors colors;

    FPSCamera fps_camera;

    unsigned int window_width_px = 700, window_height_px = 700;
    bool start_in_fullscreen = false;
    bool start_with_mouse_captured = true;
    bool vsync = false;

    Window window;
    window.initialize_glfw_glad_and_return_window(window_width_px, window_height_px, "catmullrom camera interpolation",
                                                  start_in_fullscreen, start_with_mouse_captured, vsync);

    InputState input_state;

    std::vector<ShaderType> requested_shaders = {ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_SOLID_COLOR};
    ShaderCache shader_cache(requested_shaders);
    Batcher batcher(shader_cache);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
    shader_cache.set_uniform(ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_SOLID_COLOR,
                             ShaderUniformVariable::RGBA_COLOR, glm::vec4(colors.cyan, 1));

    std::function<void(unsigned int)> char_callback = [](unsigned int codepoint) {};
    std::function<void(int, int, int, int)> key_callback = [&](int key, int scancode, int action, int mods) {
        input_state.glfw_key_callback(key, scancode, action, mods);
    };
    std::function<void(double, double)> mouse_pos_callback = [&](double xpos, double ypos) {
        fps_camera.mouse_callback(xpos, ypos);
    };
    std::function<void(int, int, int)> mouse_button_callback = [&](int button, int action, int mods) {
        input_state.glfw_mouse_button_callback(button, action, mods);
    };
    std::function<void(int, int)> frame_buffer_size_callback = [](int width, int height) {};
    GLFWLambdaCallbackManager glcm(window.glfw_window, char_callback, key_callback, mouse_pos_callback,
                                   mouse_button_callback, frame_buffer_size_callback);

    glm::mat4 identity = glm::mat4(1);
    shader_cache.set_uniform(ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_SOLID_COLOR,
                             ShaderUniformVariable::CAMERA_TO_CLIP,
                             fps_camera.get_projection_matrix(window_width_px, window_height_px));

    GLuint ltw_matrices_gl_name;
    BoundedUniqueIDGenerator ltw_id_generator(1024);
    glm::mat4 ltw_matrices[1024];

    // initialize all matrices to identity matrices
    for (int i = 0; i < 1024; ++i) {
        ltw_matrices[i] = identity;
    }

    glGenBuffers(1, &ltw_matrices_gl_name);
    glBindBuffer(GL_UNIFORM_BUFFER, ltw_matrices_gl_name);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(ltw_matrices), ltw_matrices, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ltw_matrices_gl_name);

    auto cam_indicator_ivp = vertex_geometry::generate_cylinder(16, 1, .12);
    vertex_geometry::translate_vertices_in_place(cam_indicator_ivp.xyz_positions, glm::vec3(0, -1, 0));
    auto cone = vertex_geometry::generate_cone(16, 1, .25);
    vertex_geometry::merge_ivps(cam_indicator_ivp, cone);
    vertex_geometry::rotate_vertices_in_place(cam_indicator_ivp.xyz_positions, glm::vec3(.25, 0.5, 0));
    draw_info::TransformedIVPGroup cam_indicator_tig_for_copying({cam_indicator_ivp}, ltw_id_generator.get_id());
    std::vector<draw_info::TransformedIVPGroup> cam_indicators;

    int camera_quad_strip_ltw_id = ltw_id_generator.get_id();
    std::unique_ptr<draw_info::IndexedVertexPositions> camera_quad_strip_ivp;
    std::vector<Transform> cmr_sampled_transforms;

    std::vector<std::pair<glm::vec3, glm::vec3>> fake_spline_pos_and_tangent_vec;

    int ball_ltw_id = ltw_id_generator.get_id();
    /*auto ball = vertex_geometry::generate_icosphere(3, 1);*/
    auto ball = vertex_geometry::generate_cylinder(8, 1, 1);
    Transform ball_transform;

    double duration = 10.0;
    double tau = 0.5f;

    // NOTE: if the interpolators inside scripted transform were public I wouldn't have to do this,
    // not caring for right now.
    CatmullRomInterpolator cmr(duration, tau);

    bool camera_is_controlled_by_scripted_transform = false;
    ScriptedTransform cmr_scripted_transform(duration, tau);
    int num_samples = 1000;

    std::function<void(double)> tick = [&](double dt) {
        /*glfwGetFramebufferSize(window, &width, &height);*/

        glViewport(0, 0, window_width_px, window_width_px);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fps_camera.process_input(input_state.is_pressed(EKey::LEFT_CONTROL), input_state.is_pressed(EKey::TAB),
                                 input_state.is_pressed(EKey::w), input_state.is_pressed(EKey::a),
                                 input_state.is_pressed(EKey::s), input_state.is_pressed(EKey::d),
                                 input_state.is_pressed(EKey::SPACE), input_state.is_pressed(EKey::LEFT_SHIFT), dt);

        if (input_state.is_just_pressed(EKey::q)) {
            auto cam_indicator_tig_copy = cam_indicator_tig_for_copying;
            cam_indicator_tig_copy.id = ltw_id_generator.get_id();
            for (auto &ivp : cam_indicator_tig_copy.ivps) {
                ivp.id = GlobalUIDGenerator::get_id();
            }
            cam_indicator_tig_copy.transform.set_transform_matrix(create_position_and_look_transform(
                fps_camera.transform.get_translation(), fps_camera.transform.compute_forward_vector()));
            // TODO: figure out why think has to dowith the way Look at works opposite movement somethin something
            /*cam_indicator_tig_copy.transform.rotation *= -1;*/
            p(cam_indicator_tig_copy.transform);
            cam_indicators.push_back(cam_indicator_tig_copy);

            fake_spline_pos_and_tangent_vec.push_back(
                {cam_indicator_tig_copy.transform.get_translation(), fps_camera.transform.compute_forward_vector()});
            cmr.append_point(fps_camera.transform.get_translation()); // delete
            cmr_scripted_transform.append_keyframe(fps_camera.transform);
        }

        if (input_state.is_just_pressed(EKey::p)) {

            std::function<glm::vec3(double)> f = [&](double t) { return cmr.interpolate(t); };
            /*std::function<glm::vec3(double)> f = [](double t) { return glm::vec3(std::cos(2 * t), std::sin(t), t);
             * };*/

            double t_start = 0.0;
            double t_end = duration;
            double step_size = 0.01;
            double radius = 0.1;
            double finite_diff_delta = 1e-5;

            std::vector<std::pair<glm::vec3, glm::vec3>> camera_direction_lines;

            // TODO: reset the  cmr_scripted_transform instead of copying in the future
            auto cmr_scripted_transform_copy = cmr_scripted_transform;
            double t_curr = t_start;
            while (t_curr <= t_end) {
                auto interpolated_transform = cmr_scripted_transform_copy.interpolate_transform(step_size);
                std::pair<glm::vec3, glm::vec3> line(interpolated_transform.get_translation(),
                                                     interpolated_transform.get_translation() +
                                                         interpolated_transform.compute_forward_vector());

                t_curr += step_size;
                camera_direction_lines.push_back(line);
            }

            camera_quad_strip_ivp = std::make_unique<draw_info::IndexedVertexPositions>(
                vertex_geometry::generate_quad_strip(camera_direction_lines));
        }

        if (input_state.is_just_pressed(EKey::r)) {
            camera_is_controlled_by_scripted_transform = not camera_is_controlled_by_scripted_transform;
        }

        if (camera_is_controlled_by_scripted_transform) {
            cmr_scripted_transform.update(dt);
            fps_camera.transform = cmr_scripted_transform.transform;
        }

        shader_cache.set_uniform(ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_SOLID_COLOR,
                                 ShaderUniformVariable::WORLD_TO_CAMERA, fps_camera.get_view_matrix());

        // DRAWING START
        if (camera_quad_strip_ivp) {

            std::vector<unsigned int> cam_ltw_indices(camera_quad_strip_ivp->xyz_positions.size(),
                                                      camera_quad_strip_ltw_id);
            batcher.cwl_v_transformation_ubos_1024_with_solid_color_shader_batcher.queue_draw(
                camera_quad_strip_ivp->id, camera_quad_strip_ivp->indices, camera_quad_strip_ivp->xyz_positions,
                cam_ltw_indices);
            ltw_matrices[camera_quad_strip_ltw_id] = glm::mat4(1); // doesn't move
        }

        std::vector<unsigned int> ltw_indices(ball.xyz_positions.size(), ball_ltw_id);
        batcher.cwl_v_transformation_ubos_1024_with_solid_color_shader_batcher.queue_draw(
            ball.id, ball.indices, ball.xyz_positions, ltw_indices);

        ltw_matrices[ball_ltw_id] = ball_transform.get_transform_matrix();

        for (auto &cam_indicator_tig : cam_indicators) {
            for (const auto &ivp : cam_indicator_tig.ivps) {
                std::vector<unsigned int> ltw_indices(ivp.xyz_positions.size(), cam_indicator_tig.id);
                batcher.cwl_v_transformation_ubos_1024_with_solid_color_shader_batcher.queue_draw(
                    ivp.id, ivp.indices, ivp.xyz_positions, ltw_indices);
            }

            /*p("tiggy");*/
            /*p(cam_indicator_tig.transform);*/
            ltw_matrices[cam_indicator_tig.id] = cam_indicator_tig.transform.get_transform_matrix();
        }

        batcher.cwl_v_transformation_ubos_1024_with_solid_color_shader_batcher.draw_everything();

        // DRAWING END

        glBindBuffer(GL_UNIFORM_BUFFER, ltw_matrices_gl_name);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ltw_matrices), ltw_matrices);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glfwSwapBuffers(window.glfw_window);
        glfwPollEvents();

        TemporalBinarySignal::process_all();
    };

    std::function<bool()> termination = [&]() { return glfwWindowShouldClose(window.glfw_window); };

    FixedFrequencyLoop ffl;
    ffl.start(120, tick, termination);

    return 0;
}
