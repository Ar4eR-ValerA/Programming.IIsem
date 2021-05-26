#ifndef LAB_6_CUBE_ALGORITHMS_H
#define LAB_6_CUBE_ALGORITHMS_H
#include "cube/cube.h"
#include "cube/color.h"

class cube_algorithms {
private:
    static void chamomile_front_sides(cube& cube_);

    static void chamomile_lower(cube& cube_);

    static void chamomile_front_upper(cube& cube_);

    static void chamomile_front_lower(cube& cube_);

    static void white_cross_rotate(cube& cube_, color color_);

    static void bang_bang(cube& cube_, int count);

    static void first_layer_find_corner(cube& cube_, color color1, color color2);

    static void first_layer_lower_corner(cube& cube_);

    static void second_layer_to_right(cube& cube_);

    static void second_layer_to_left(cube& cube_);

    static void second_layer_left_to_up(cube& cube_);

    static void second_layer_right_to_up(cube& cube_);

    static bool is_second_layer_assembled(cube& cube_);

    static void yellow_edges_rotate(cube& cube_);

    static bool is_yellow_edges_assembled(cube& cube_);

    static void upper_corners_rotate(cube& cube_);

    static bool is_correct_front_upper_corner(cube& cube_);

    static bool is_correct_upper_corners_exist(cube& cube_);

    static bool is_correct_upper_corners(cube& cube_);

public:
    static void yellow_to_up(cube& cube_);

    static void chamomile(cube& cube_);

    static void white_cross(cube& cube_);

    static void first_layer(cube& cube_);

    static void second_layer(cube& cube_);

    static void yellow_cross(cube& cube_);

    static void yellow_edges(cube& cube_);

    static void upper_corners(cube& cube_);

    static void corners_rotate(cube& cube_);

    static void assemble(cube& cube_);
};

#endif //LAB_6_CUBE_ALGORITHMS_H