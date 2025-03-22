#include "grid_font.hpp"

std::string zero = R"(
-*****-
-*---*-
-*---*-
-*---*-
-*****-
)";

std::string one = R"(
---*---
---*---
---*---
---*---
---*---
)";

std::string two = R"(
-*****-
-----*-
-*****-
-*-----
-*****-
)";

std::string three = R"(
-*****-
-----*-
-*****-
-----*-
-*****-
)";

std::string four = R"(
-*---*-
-*---*-
-*****-
-----*-
-----*-
)";

std::string five = R"(
-*****-
-*-----
-*****-
-----*-
-*****-
)";

std::string six = R"(
-*****-
-*-----
-*****-
-*---*-
-*****-
)";

std::string seven = R"(
-*****-
-----*-
-----*-
-----*-
-----*-
)";

std::string eight = R"(
-*****-
-*---*-
-*****-
-*---*-
-*****-
)";

std::string nine = R"(
-*****-
-*---*-
-*****-
-----*-
-*****-
)";

std::string a_upper = R"(
--***--
-*---*-
-*****-
-*---*-
-*---*-
)";

std::string b_upper = R"(
-****--
-*---*-
-****--
-*---*-
-****--
)";

std::string c_upper = R"(
-*****-
-*-----
-*-----
-*-----
-*****-
)";

std::string d_upper = R"(
-****--
-*---*-
-*---*-
-*---*-
-****--
)";

std::string e_upper = R"(
-*****-
-*-----
-****--
-*-----
-*****-
)";

std::string f_upper = R"(
-*****-
-*-----
-****--
-*-----
-*-----
)";

std::string g_upper = R"(
-*****-
-*-----
-*--**-
-*---*-
-*****-
)";

std::string h_upper = R"(
-*---*-
-*---*-
-*****-
-*---*-
-*---*-
)";

std::string i_upper = R"(
--***--
---*---
---*---
---*---
--***--
)";

std::string j_upper = R"(
---***-
----*--
----*--
-*--*--
--**---
)";

std::string k_upper = R"(
-*---*-
-*--*--
-***---
-*--*--
-*---*-
)";

std::string l_upper = R"(
-*-----
-*-----
-*-----
-*-----
-*****-
)";

std::string m_upper = R"(
-*---*-
-**-**-
-*-* *-
-*---*-
-*---*-
)";

std::string n_upper = R"(
-*---*-
-**--*-
-*-* *-
-*--**-
-*---*-
)";

std::string o_upper = R"(
-*****-
-*---*-
-*---*-
-*---*-
-*****-
)";

std::string p_upper = R"(
-****--
-*---*-
-****--
-*-----
-*-----
)";

std::string q_upper = R"(
-*****-
-*---*-
-*---*-
-*--**-
-*****-
)";

std::string r_upper = R"(
-****--
-*---*-
-****--
-*--*--
-*---*-
)";

std::string s_upper = R"(
-*****-
-*-----
-*****-
-----*-
-*****-
)";

std::string t_upper = R"(
-*****-
---*---
---*---
---*---
---*---
)";

std::string u_upper = R"(
-*---*-
-*---*-
-*---*-
-*---*-
-*****-
)";

std::string v_upper = R"(
-*---*-
-*---*-
-*---*-
--*-*--
---*---
)";

std::string w_upper = R"(
-*---*-
-*---*-
-* * *-
-**-**-
-*---*-
)";

std::string x_upper = R"(
-*---*-
--*-*--
---*---
--*-*--
-*---*-
)";

std::string y_upper = R"(
-*---*-
--*-*--
---*---
---*---
---*---
)";

std::string z_upper = R"(
-*****-
----*--
---*---
--*----
-*****-
)";

std::string a_lower = R"(
--------
--***---
-*---*--
-*****--
-*---*--
)";

std::string b_lower = R"(
-*------
-*------
-****---
-*---*--
-****---
)";

std::string c_lower = R"(
--------
--****--
-*------
-*------
--****--
)";

std::string d_lower = R"(
------*-
------*-
--*****-
-*----*-
--****--
)";

std::string e_lower = R"(
--------
--****--
-*****--
-*------
--****--
)";

std::string f_lower = R"(
----**--
---*----
--***---
---*----
---*----
)";

std::string g_lower = R"(
--------
--****--
-*---*--
--****--
-----*--
)";

std::string h_lower = R"(
-*------
-*------
-****---
-*---*--
-*---*--
)";

std::string i_lower = R"(
----*---
--------
---**---
----*---
---***--
)";

std::string j_lower = R"(
------*-
--------
-----**-
------*-
--****--
)";

std::string k_lower = R"(
-*------
-*---*--
-**-*---
-*--*---
-*---*--
)";

std::string l_lower = R"(
---**---
----*---
----*---
----*---
---***--
)";

std::string m_lower = R"(
--------
-****---
-*-*-*--
-*-*-*--
-*-*-*--
)";

std::string n_lower = R"(
--------
-****---
-*---*--
-*---*--
-*---*--
)";

std::string o_lower = R"(
--------
--****--
-*----*-
-*----*-
--****--
)";

std::string p_lower = R"(
--------
-****---
-*---*--
-*****--
-*------
)";

std::string q_lower = R"(
--------
--****--
-*----*-
-*----*-
--****-*
)";

std::string r_lower = R"(
--------
-****---
-*---*--
-*****--
-*---*--
)";

std::string s_lower = R"(
--------
--****--
-*------
--****--
-----*--
)";

std::string t_lower = R"(
-*****--
----*---
----*---
----*---
----*---
)";

std::string u_lower = R"(
-*----*-
-*----*-
-*----*-
--****--
-------- 
)";

std::string v_lower = R"(
-*----*-
-*----*-
-*----*-
--****--
-------- 
)";

std::string w_lower = R"(
-*----*-
-*----*-
-*-*-*--
-*-*-*--
-*-*-*--
)";

std::string x_lower = R"(
-*---*--
--*-*---
---*----
--*-*---
-*---*--
)";

std::string y_lower = R"(
-*---*--
--*_*---
---*----
----*---
----*---
)";

std::string z_lower = R"(
-*****--
-----*--
----*---
---*----
-*****--
)";


std::string exclamation = R"(
---*---
---*---
---*---
-------
---*---
)";

std::string question = R"(
-*****-
----*--
---*---
-------
---*---
)";

std::string hash = R"(
--*-*--
-*****-
--*-*--
-*****-
--*-*--
)";

std::string dollar = R"(
---*---
-*****-
-*-*---
-*****-
---*---
)";

std::string percent = R"(
-**--*-
-**-*--
---*---
--*-**-
-*--**-
)";

std::string ampersand = R"(
--**---
-*--*--
--**---
-*--*-*
--**-*-
)";

std::string asterisk = R"(
---*---
-*-*-*-
---*---
--*-*--
-*---*-
)";

std::string at_symbol = R"(
-*****-
-*---*-
-*--**-
-*----*
-*****-
)";

std::string period = R"(
-------
-------
-------
-------
---*---
)";

std::string comma = R"(
-------
-------
-------
--*----
-*-----
)";

std::string colon = R"(
-------
---*---
-------
---*---
-------
)";

std::string angle_bracket_left = R"(
----*--
---*---
--*----
---*---
----*--
)";

std::string angle_bracket_right = R"(
--*----
---*---
----*--
---*---
--*----
)";

std::string parenthesis_left = R"(
--***--
-*-----
-*-----
-*-----
--***--
)";

std::string parenthesis_right = R"(
--***--
-----*-
-----*-
-----*-
--***--
)";

std::unordered_map<char, std::string> character_to_text_grid = {
    {'0', zero},
    {'1', one},
    {'2', two},
    {'3', three},
    {'4', four},
    {'5', five},
    {'6', six},
    {'7', seven},
    {'8', eight},
    {'9', nine},
    {'A', a_upper},
    {'B', b_upper},
    {'C', c_upper},
    {'D', d_upper},
    {'E', e_upper},
    {'F', f_upper},
    {'G', g_upper},
    {'H', h_upper},
    {'I', i_upper},
    {'J', j_upper},
    {'K', k_upper},
    {'L', l_upper},
    {'M', m_upper},
    {'N', n_upper},
    {'O', o_upper},
    {'P', p_upper},
    {'Q', q_upper},
    {'R', r_upper},
    {'S', s_upper},
    {'T', t_upper},
    {'U', u_upper},
    {'V', v_upper},
    {'W', w_upper},
    {'X', x_upper},
    {'Y', y_upper},
    {'Z', z_upper},
    {'a', a_lower},
    {'b', b_lower},
    {'c', c_lower},
    {'d', d_lower},
    {'e', e_lower},
    {'f', f_lower},
    {'g', g_lower},
    {'h', h_lower},
    {'i', i_lower},
    {'j', j_lower},
    {'k', k_lower},
    {'l', l_lower},
    {'m', m_lower},
    {'n', n_lower},
    {'o', o_lower},
    {'p', p_lower},
    {'q', q_lower},
    {'r', r_lower},
    {'s', s_lower},
    {'t', t_lower},
    {'u', u_lower},
    {'v', v_lower},
    {'w', w_lower},
    {'x', x_lower},
    {'y', y_lower},
    {'z', z_lower},
    {'!', exclamation},
    {'?', question},
    {'#', hash},
    {'$', dollar},
    {'%', percent},
    {'&', ampersand},
    {'*', asterisk},
    {'@', at_symbol},
    {'.', period},
    {',', comma},
    {':', colon},
    {'<', angle_bracket_left},
    {'>', angle_bracket_right},
    {'(', parenthesis_left},
    {')', parenthesis_right}
};



std::string strip_leading_newlines(const std::string &text) {
    size_t start = 0;
    while (start < text.size() && text[start] == '\n') {
        ++start;
    }
    return text.substr(start);
}

draw_info::IndexedVertexPositions text_grid_to_rect_grid(const std::string &text_grid,
                                                         const vertex_geometry::Rectangle bounding_rect) {
    unsigned int rows = 0;
    unsigned int cols = 0;

    // count rows and columns based on text_grid.
    std::vector<std::string> lines;
    std::string line;
    std::string cleaned_text_grid = strip_leading_newlines(text_grid);

    for (char c : cleaned_text_grid) {
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        } else {
            line += c;
        }
    }
    if (!line.empty())
        lines.push_back(line); // for the last line if there's no final newline.

    rows = lines.size();
    if (rows > 0) {
        cols = lines[0].length(); // assuming all rows have equal length.
    }

    // Initialize grid
    vertex_geometry::Grid grid(rows, cols, bounding_rect);

    std::vector<draw_info::IndexedVertexPositions> ivps;

    // iterate over the grid and collect indexed vertex positions for '*' characters.
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            if (lines[row][col] == '*') {
                vertex_geometry::Rectangle rect = grid.get_at(col, row);
                vertex_geometry::IndexedVertices ivs = rect.get_ivs();
                draw_info::IndexedVertexPositions ivp(ivs.indices, ivs.vertices);
                ivps.push_back(ivp);
            }
        }
    }

    return vertex_geometry::merge_ivps(ivps);
}




draw_info::IndexedVertexPositions get_text_geometry(const std::string &text, vertex_geometry::Rectangle bounding_rect) {


    std::vector<draw_info::IndexedVertexPositions> character_ivps;

    vertex_geometry::Grid grid(1, text.size(), bounding_rect);
    unsigned int count = 0;
    for (const char ch : text) {
        std::string text_grid = character_to_text_grid[ch];
        auto character_bounding_rect = grid.get_at(count, 0);
        character_ivps.push_back(text_grid_to_rect_grid(text_grid, character_bounding_rect));
        count++;
    }

    auto text_geom = vertex_geometry::merge_ivps(character_ivps);
    vertex_geometry::scale_vertices_in_place(text_geom.xyz_positions, glm::vec3(4, 1, 1));
    return text_geom;
}
