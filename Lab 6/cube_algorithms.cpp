#include "cube_algorithms.h"
#include <stdexcept>
#include <unistd.h>
#include <iostream>

void cube_algorithms::yellow_to_up(cube& cube_) {
    cube_.print();

    if (cube_.get_upper()[1][1] == yellow) {
        return;
    }
    else if (cube_.get_left()[1][1] == yellow) {
        cube_.rotate_cube_to_right();
    }
    else if (cube_.get_back()[1][1] == yellow) {
        cube_.rotate_cube_to_down();
    }
    else if (cube_.get_right()[1][1] == yellow) {
        cube_.rotate_cube_to_left();
    }
    else if (cube_.get_front()[1][1] == yellow) {
        cube_.rotate_cube_to_up();
    }
    else if (cube_.get_lower()[1][1] == yellow) {
        cube_.rotate_cube_to_up();
        cube_.rotate_cube_to_up();
    }

    std::cout << "Yellow to up\n";
    cube_.print();
    sleep(3);
}

void cube_algorithms::chamomile_front_sides(cube &cube_) {
    if (cube_.get_front()[1][0] == white) {
        while (cube_.get_upper()[1][0] == white) {
            cube_.rotate_upper_to_right();
        }

        cube_.rotate_left_to_up();
    }
    if (cube_.get_front()[1][2] == white) {
        while (cube_.get_upper()[1][2] == white) {
            cube_.rotate_upper_to_right();
        }

        cube_.rotate_right_to_up();
    }
}

void cube_algorithms::chamomile_lower(cube &cube_) {
    if (cube_.get_lower()[1][2] == white) {
        while (cube_.get_upper()[1][2] == white) {
            cube_.rotate_upper_to_right();
        }

        cube_.rotate_right_to_up();
        cube_.rotate_right_to_up();
    }
}

void cube_algorithms::chamomile_front_upper(cube &cube_) {
    if (cube_.get_front()[0][1] == white) {
        cube_.rotate_front_to_right();

        chamomile_front_sides(cube_);
    }
}

void cube_algorithms::chamomile_front_lower(cube &cube_) {
    if (cube_.get_front()[2][1] == white) {
        cube_.rotate_front_to_left();

        chamomile_front_sides(cube_);
    }
}

void cube_algorithms::chamomile(cube &cube_) {
    yellow_to_up(cube_);

    for (int i = 0; i < 4; ++i) {
        chamomile_front_sides(cube_);

        cube_.rotate_cube_to_right();
    }

    for (int i = 0; i < 4; ++i) {
        chamomile_lower(cube_);

        cube_.rotate_cube_to_right();
    }

    for (int i = 0; i < 4; ++i) {
        chamomile_front_upper(cube_);

        cube_.rotate_cube_to_right();
    }

    for (int i = 0; i < 4; ++i) {
        chamomile_front_lower(cube_);

        cube_.rotate_cube_to_right();
    }

    for (int i = 0; i < 4; ++i) {
        chamomile_front_sides(cube_);

        cube_.rotate_cube_to_right();
    }

    if (!(cube_.get_upper()[1][0] == white && cube_.get_upper()[2][1] == white && cube_.get_upper()[1][2] == white && cube_.get_upper()[0][1] == white)) {
        throw std::logic_error("Chamomile error");
    }

    std::cout << "Chamomile\n";
    cube_.print();
    sleep(3);
}

void cube_algorithms::white_cross_rotate(cube &cube_, color color_) {
    int count = 0;
    while (cube_.get_front()[0][1] != color_ || cube_.get_upper()[2][1] != white) {
        cube_.rotate_cube_to_right();
        count++;

        if (count > 4) {
            throw std::logic_error("White cross error");
        }
    }

    count = 0;

    while (cube_.get_front()[0][1] != cube_.get_front()[1][1]) {
        cube_.rotate_upper_to_right();
        cube_.rotate_cube_to_left();
        count++;

        if (count > 4) {
            throw std::logic_error("White cross error");
        }
    }

    cube_.rotate_front_to_right();
    cube_.rotate_front_to_right();
}

void cube_algorithms::white_cross(cube &cube_) {
    chamomile(cube_);

    white_cross_rotate(cube_, red);
    white_cross_rotate(cube_, blue);
    white_cross_rotate(cube_, green);
    white_cross_rotate(cube_, orange);

    std::cout << "White cross\n";
    cube_.print();
    sleep(3);
}

void cube_algorithms::bang_bang(cube &cube_, int count) {
    for (int i = 0; i < count; ++i) {
        cube_.rotate_right_to_up();
        cube_.rotate_upper_to_left();
        cube_.rotate_right_to_down();
        cube_.rotate_upper_to_right();
    }
}

void cube_algorithms::first_layer_find_corner(cube& cube_, color color1, color color2) {
    for (int i = 0; i < 4; ++i) {
        if (cube_.get_front()[0][2] == color1 && cube_.get_upper()[2][2] == color2 && cube_.get_right()[0][0] == white) {
            bang_bang(cube_, 1);
            return;
        }
        else if (cube_.get_front()[0][2] == color2 && cube_.get_upper()[2][2] == white && cube_.get_right()[0][0] == color1) {
            bang_bang(cube_, 3);
            return;
        }
        else if (cube_.get_front()[0][2] == white && cube_.get_upper()[2][2] == color1 && cube_.get_right()[0][0] == color2) {
            bang_bang(cube_, 5);
            return;
        }
        else {
            cube_.rotate_upper_to_right();
        }
    }
}

void cube_algorithms::first_layer_lower_corner(cube &cube_) {
    if (cube_.get_front()[2][2] == white || cube_.get_right()[2][0] == white) {
        bang_bang(cube_, 1);
    }
}

void cube_algorithms::first_layer(cube &cube_) {
    white_cross(cube_);

    int count = 0;
    while (!(cube_.get_lower()[0][0] == white && cube_.get_lower()[2][0] == white && cube_.get_lower()[2][2] == white && cube_.get_lower()[0][2] == white)) {
        first_layer_find_corner(cube_, cube_.get_front()[1][1], cube_.get_right()[1][1]);
        cube_.rotate_cube_to_left();

        for (int i = 0; i < 4; ++i) {
            first_layer_lower_corner(cube_);
            cube_.rotate_cube_to_left();
        }
        count++;
        if (count == 100) {
            throw std::logic_error("First layer error");
        }
    }

    std::cout << "First layer\n";
    cube_.print();
    sleep(3);
}

void cube_algorithms::second_layer_to_right(cube &cube_) {
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_up();
    cube_.rotate_upper_to_right();
    cube_.rotate_right_to_down();
    cube_.rotate_upper_to_right();
    cube_.rotate_front_to_left();
    cube_.rotate_upper_to_left();
    cube_.rotate_front_to_right();
}

void cube_algorithms::second_layer_to_left(cube &cube_) {
    cube_.rotate_upper_to_right();
    cube_.rotate_left_to_up();
    cube_.rotate_upper_to_left();
    cube_.rotate_left_to_down();
    cube_.rotate_upper_to_left();
    cube_.rotate_front_to_right();
    cube_.rotate_upper_to_right();
    cube_.rotate_front_to_left();
}

bool cube_algorithms::is_second_layer_assembled(cube &cube_) {
    if (cube_.get_front()[1][0] != cube_.get_front()[1][1] || cube_.get_front()[1][2] != cube_.get_front()[1][1]) {
        return false;
    }

    if (cube_.get_right()[1][0] != cube_.get_right()[1][1] || cube_.get_right()[1][2] != cube_.get_right()[1][1]) {
        return false;
    }

    if (cube_.get_left()[1][0] != cube_.get_left()[1][1] || cube_.get_left()[1][2] != cube_.get_left()[1][1]) {
        return false;
    }

    if (cube_.get_back()[1][0] != cube_.get_back()[1][1] || cube_.get_back()[1][2] != cube_.get_back()[1][1]) {
        return false;
    }

    return true;
}

void cube_algorithms::second_layer_right_to_up(cube& cube_) {
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_up();
    cube_.rotate_upper_to_right();
    cube_.rotate_right_to_down();
    cube_.rotate_upper_to_right();
    cube_.rotate_front_to_left();
    cube_.rotate_upper_to_left();
    cube_.rotate_front_to_right();
}

void cube_algorithms::second_layer_left_to_up(cube& cube_) {
    cube_.rotate_upper_to_right();
    cube_.rotate_left_to_up();
    cube_.rotate_upper_to_left();
    cube_.rotate_left_to_down();
    cube_.rotate_upper_to_left();
    cube_.rotate_front_to_right();
    cube_.rotate_upper_to_right();
    cube_.rotate_front_to_left();
}

void cube_algorithms::second_layer(cube &cube_) {
    first_layer(cube_);

    int count = 0;

    while (!is_second_layer_assembled(cube_)) {

        for (int i = 0; i < 4; ++i) {
            if (cube_.get_front()[0][1] == cube_.get_front()[1][1] && cube_.get_upper()[2][1] == cube_.get_right()[1][1]) {
                second_layer_to_right(cube_);
                break;
            }

            if (cube_.get_front()[0][1] == cube_.get_front()[1][1] && cube_.get_upper()[2][1] == cube_.get_left()[1][1]) {
                second_layer_to_left(cube_);
                break;
            }

            cube_.rotate_upper_to_right();
        }

        for (int i = 0; i < 4; ++i) {
            if (cube_.get_front()[1][2] != cube_.get_front()[1][1] || cube_.get_right()[1][0] != cube_.get_right()[1][1]) {
                second_layer_right_to_up(cube_);
                break;
            }

            if (cube_.get_front()[1][0] != cube_.get_front()[1][1] || cube_.get_left()[1][2] != cube_.get_left()[1][1]) {
                second_layer_left_to_up(cube_);
                break;
            }

            cube_.rotate_cube_to_right();
        }

        cube_.rotate_cube_to_right();
        count++;
        if (count == 100) {
            throw std::logic_error("Second layer error");
        }
    }

    std::cout << "Second layer\n";
    cube_.print();
    sleep(3);
}

void cube_algorithms::yellow_cross(cube& cube_) {
    second_layer(cube_);

    if (cube_.get_upper()[0][1] == yellow && cube_.get_upper()[1][0] == yellow && cube_.get_upper()[2][1] == yellow && cube_.get_upper()[1][2] == yellow) {
        std::cout << "Yellow cross\n";
        cube_.print();
        sleep(3);
        return;
    }

    if (cube_.get_upper()[0][1] != yellow && cube_.get_upper()[1][0] != yellow && cube_.get_upper()[2][1] != yellow && cube_.get_upper()[1][2] != yellow) {
        cube_.rotate_front_to_right();
        bang_bang(cube_, 1);
        cube_.rotate_front_to_left();
    }

    for (int i = 0; i < 4; ++i) {
        if (cube_.get_upper()[1][0] == yellow && cube_.get_upper()[0][1] == yellow) {
            cube_.rotate_front_to_right();
            bang_bang(cube_, 2);
            cube_.rotate_front_to_left();

            std::cout << "Yellow cross\n";
            cube_.print();
            sleep(3);
            return;
        }
        cube_.rotate_cube_to_right();
    }

    for (int i = 0; i < 2; ++i) {
        if (cube_.get_upper()[1][0] == yellow && cube_.get_upper()[1][2] == yellow) {
            cube_.rotate_front_to_right();
            bang_bang(cube_, 1);
            cube_.rotate_front_to_left();

            std::cout << "Yellow cross\n";
            cube_.print();
            sleep(3);
            return;
        }
        cube_.rotate_cube_to_right();
    }
}

void cube_algorithms::yellow_edges_rotate(cube& cube_) {
    cube_.rotate_right_to_up();
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_down();
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_up();
    cube_.rotate_upper_to_left();
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_down();
}

bool cube_algorithms::is_yellow_edges_assembled(cube& cube_) {
    if (cube_.get_right()[0][1] != cube_.get_right()[1][1]) {
        return false;
    }
    if (cube_.get_back()[0][1] != cube_.get_back()[1][1]) {
        return false;
    }
    if (cube_.get_left()[0][1] != cube_.get_left()[1][1]) {
        return false;
    }
    if (cube_.get_front()[0][1] != cube_.get_front()[1][1]) {
        return false;
    }
    return true;
}

void cube_algorithms::yellow_edges(cube& cube_) {
    yellow_cross(cube_);

    if (is_yellow_edges_assembled(cube_)) {
        std::cout << "Yellow edges\n";
        cube_.print();
        sleep(3);
        return;
    }

    while (cube_.get_front()[0][1] != cube_.get_front()[1][1]) {
        cube_.rotate_upper_to_left();
    }

    if (cube_.get_right()[0][1] == cube_.get_right()[1][1] && cube_.get_back()[0][1] != cube_.get_back()[1][1] && cube_.get_left()[0][1] != cube_.get_left()[1][1]) {
        cube_.rotate_upper_to_left();
    }
    else if (cube_.get_right()[0][1] != cube_.get_right()[1][1] && cube_.get_back()[0][1] != cube_.get_back()[1][1] && cube_.get_left()[0][1] == cube_.get_left()[1][1]) {
        cube_.rotate_upper_to_right();
    }
    else if (cube_.get_back()[0][1] == cube_.get_back()[1][1]) {
        yellow_edges_rotate(cube_);
    }

    if (cube_.get_right()[0][1] != cube_.get_right()[1][1] && cube_.get_back()[0][1] != cube_.get_back()[1][1] && cube_.get_left()[0][1] != cube_.get_left()[1][1]) {
        while (!is_yellow_edges_assembled(cube_)) {
            yellow_edges_rotate(cube_);
        }
    }

    std::cout << "Yellow edges\n";
    cube_.print();
    sleep(3);
}

bool cube_algorithms::is_correct_front_upper_corner(cube& cube_) {
    color color1 = yellow;
    color color2 = cube_.get_front()[1][1];
    color color3 = cube_.get_right()[1][1];

    if (cube_.get_front()[0][2] == color1 && cube_.get_upper()[2][2] == color2 && cube_.get_right()[0][0] == color3) {
        return true;
    }

    if (cube_.get_front()[0][2] == color1 && cube_.get_upper()[2][2] == color3 && cube_.get_right()[0][0] == color2) {
        return true;
    }

    if (cube_.get_front()[0][2] == color2 && cube_.get_upper()[2][2] == color1 && cube_.get_right()[0][0] == color3) {
        return true;
    }

    if (cube_.get_front()[0][2] == color2 && cube_.get_upper()[2][2] == color3 && cube_.get_right()[0][0] == color1) {
        return true;
    }

    if (cube_.get_front()[0][2] == color3 && cube_.get_upper()[2][2] == color1 && cube_.get_right()[0][0] == color2 ) {
        return true;
    }

    if (cube_.get_front()[0][2] == color3 && cube_.get_upper()[2][2] == color2 && cube_.get_right()[0][0] == color1) {
        return true;
    }

    return false;
}

bool cube_algorithms::is_correct_upper_corners_exist(cube& cube_) {
    for (int i = 0; i < 4; ++i) {
        if (is_correct_front_upper_corner(cube_)) {
            return true;
        }
        cube_.rotate_cube_to_right();
    }

    return false;
}

bool cube_algorithms::is_correct_upper_corners(cube& cube_) {
    for (int i = 0; i < 4; ++i) {
        if (!is_correct_front_upper_corner(cube_)) {
            return false;
        }
        cube_.rotate_cube_to_right();
    }

    return true;
}

void cube_algorithms::upper_corners_rotate(cube& cube_) {
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_up();
    cube_.rotate_upper_to_right();
    cube_.rotate_left_to_up();
    cube_.rotate_upper_to_left();
    cube_.rotate_right_to_down();
    cube_.rotate_upper_to_right();
    cube_.rotate_left_to_down();
}

void cube_algorithms::upper_corners(cube& cube_) {
    yellow_edges(cube_);

    if (!is_correct_upper_corners_exist(cube_)) {
        upper_corners_rotate(cube_);
    }

    int count = 0;
    while (!is_correct_upper_corners(cube_)) {
        for (int i = 0; i < 4; ++i) {
            if (is_correct_front_upper_corner(cube_)) {

                upper_corners_rotate(cube_);
            }
            cube_.rotate_cube_to_right();
        }

        count++;
        if (count == 100) {
            throw std::logic_error("Upper corners error");
        }
    }

    std::cout << "Upper corners\n";
    cube_.print();
    sleep(3);
}

void cube_algorithms::corners_rotate(cube& cube_) {
    upper_corners(cube_);

    cube_.rotate_cube_to_up();
    cube_.rotate_cube_to_right();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (cube_.get_back()[0][2] == yellow || cube_.get_upper()[0][0] == yellow) {
                break;
            }
            cube_.rotate_left_to_down();
        }
        if (cube_.get_back()[0][2] == yellow) {
            bang_bang(cube_, 2);
        } else if (cube_.get_upper()[0][0] == yellow) {
            bang_bang(cube_, 4);
        }
    }
}

void cube_algorithms::assemble(cube& cube_) {
    corners_rotate(cube_);

    for (int i = 0; i < 4; ++i) {
        if (cube_.get_front()[1][0] == cube_.get_front()[1][1]) {

            std::cout << "Assembled\n";
            cube_.print();
            sleep(3);
            return;
        }

        cube_.rotate_left_to_up();
    }

    throw std::logic_error("Assemble error");
}