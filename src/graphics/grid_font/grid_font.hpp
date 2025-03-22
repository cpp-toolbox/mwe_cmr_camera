#ifndef GRID_FONT_HPP
#define GRID_FONT_HPP

#include "../draw_info/draw_info.hpp"
#include "../vertex_geometry/vertex_geometry.hpp"

draw_info::IndexedVertexPositions text_grid_to_rect_grid(const std::string &text_grid,
                                                         const vertex_geometry::Rectangle bounding_rect);

draw_info::IndexedVertexPositions get_text_geometry(const std::string &text, vertex_geometry::Rectangle bounding_rect);

#endif // GRID_FONT_HPP
