#include <iostream>
#include <graphics.h>
#include "cube.h"

cube::cube() :
    front_(std::vector<std::vector<color>>(3, std::vector<color>(3, stuff_c))),
    left_(std::vector<std::vector<color>>(3, std::vector<color>(3, stuff_c))),
    back_(std::vector<std::vector<color>>(3, std::vector<color>(3, stuff_c))),
    right_(std::vector<std::vector<color>>(3, std::vector<color>(3, stuff_c))),
    lower_(std::vector<std::vector<color>>(3, std::vector<color>(3, stuff_c))),
    upper_(std::vector<std::vector<color>>(3, std::vector<color>(3, stuff_c))) {}

cube::~cube() = default;

void cube::init_front(const std::vector<std::vector<color>> &side) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            front_[i][j] = side[i][j];
        }
    }
}

void cube::enter_matrix(std::vector<std::vector<color>> &matrix) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::string st;
            std::cin >> st;

            color temp;
            switch (st[0]) {
                case 'w':
                    temp = white;
                    break;

                case 'y':
                    temp = yellow;
                    break;

                case 'g':
                    temp = green;
                    break;

                case 'b':
                    temp = blue;
                    break;

                case 'o':
                    temp = orange;
                    break;

                case 'r':
                    temp = red;
                    break;
            }

            matrix[i][j] = temp;
        }
    }
}

void cube::init_left(const std::vector<std::vector<color>> &side) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            left_[i][j] = side[i][j];
        }
    }
}

void cube::init_back(const std::vector<std::vector<color>> &side) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            back_[i][j] = side[i][j];
        }
    }
}

void cube::init_right(const std::vector<std::vector<color>> &side) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            right_[i][j] = side[i][j];
        }
    }
}

void cube::init_lower(const std::vector<std::vector<color>> &side) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            lower_[i][j] = side[i][j];
        }
    }
}

void cube::init_upper(const std::vector<std::vector<color>> &side) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            upper_[i][j] = side[i][j];
        }
    }


}

void cube::rotate_matrix_to_right(std::vector<std::vector<color>> &matrix) {
    std::vector<std::vector<color>> temp(3, std::vector<color>(3, stuff_c));

    temp = matrix;
    temp[1][0] = matrix[2][1];
    temp[2][0] = matrix[2][2];
    temp[2][1] = matrix[1][2];
    temp[2][2] = matrix[0][2];
    temp[1][2] = matrix[0][1];
    temp[0][2] = matrix[0][0];
    temp[0][1] = matrix[1][0];
    temp[0][0] = matrix[2][0];
    temp[1][1] = matrix[1][1];
    matrix = temp;
}

void cube::rotate_matrix_to_left(std::vector<std::vector<color>> &matrix) {
    std::vector<std::vector<color>> temp(3, std::vector<color>(3, stuff_c));

    temp = matrix;
    temp[1][0] = matrix[0][1];
    temp[2][0] = matrix[0][0];
    temp[2][1] = matrix[1][0];
    temp[2][2] = matrix[2][0];
    temp[1][2] = matrix[2][1];
    temp[0][2] = matrix[2][2];
    temp[0][1] = matrix[1][2];
    temp[0][0] = matrix[0][2];
    temp[1][1] = matrix[1][1];
    matrix = temp;
}

void cube::rotate_lower_to_right() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    temp1 = right_[2];
    right_[2] = front_[2];

    temp2 = back_[2];
    back_[2] = temp1;

    temp1 = left_[2];
    left_[2] = temp2;

    front_[2] = temp1;

    rotate_matrix_to_right(lower_);

    print();
}

void cube::rotate_lower_to_left() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    temp1 = left_[2];
    left_[2] = front_[2];

    temp2 = back_[2];
    back_[2] = temp1;

    temp1 = right_[2];
    right_[2] = temp2;

    front_[2] = temp1;

    rotate_matrix_to_left(lower_);

    print();
}

void cube::rotate_upper_to_right() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    temp1 = right_[0];
    right_[0] = front_[0];

    temp2 = back_[0];
    back_[0] = temp1;

    temp1 = left_[0];
    left_[0] = temp2;

    front_[0] = temp1;

    rotate_matrix_to_left(upper_);

    print();
}

void cube::rotate_upper_to_left() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    temp1 = left_[0];
    left_[0] = front_[0];

    temp2 = back_[0];
    back_[0] = temp1;

    temp1 = right_[0];
    right_[0] = temp2;

    front_[0] = temp1;

    rotate_matrix_to_right(upper_);

    print();
}

void cube::rotate_right_to_up() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    for (int i = 0; i < 3; ++i) {
        temp1[i] = upper_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        upper_[i][2] = front_[i][2];
    }

    for (int i = 0; i < 3; ++i) {
        temp2[2 - i] = back_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        back_[2 - i][0] = temp1[i];
    }

    for (int i = 0; i < 3; ++i) {
        temp1[i] = lower_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        lower_[i][2] = temp2[i];
    }

    for (int i = 0; i < 3; ++i) {
        front_[i][2] = temp1[i];
    }

    rotate_matrix_to_right(right_);

    print();
}

void cube::rotate_right_to_down() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    for (int i = 0; i < 3; ++i) {
        temp1[i] = lower_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        lower_[i][2] = front_[i][2];
    }

    for (int i = 0; i < 3; ++i) {
        temp2[2 - i] = back_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        back_[2 - i][0] = temp1[i];
    }

    for (int i = 0; i < 3; ++i) {
        temp1[i] = upper_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        upper_[i][2] = temp2[i];
    }

    for (int i = 0; i < 3; ++i) {
        front_[i][2] = temp1[i];
    }

    rotate_matrix_to_left(right_);

    print();
}

void cube::rotate_left_to_up() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    for (int i = 0; i < 3; ++i) {
        temp1[i] = upper_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        upper_[i][0] = front_[i][0];
    }

    for (int i = 0; i < 3; ++i) {
        temp2[2 - i] = back_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        back_[2 - i][2] = temp1[i];
    }

    for (int i = 0; i < 3; ++i) {
        temp1[i] = lower_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        lower_[i][0] = temp2[i];
    }

    for (int i = 0; i < 3; ++i) {
        front_[i][0] = temp1[i];
    }

    rotate_matrix_to_left(left_);

    print();
}

void cube::rotate_left_to_down() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    for (int i = 0; i < 3; ++i) {
        temp1[i] = lower_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        lower_[i][0] = front_[i][0];
    }

    for (int i = 0; i < 3; ++i) {
        temp2[2 - i] = back_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        back_[2 - i][2] = temp1[i];
    }

    for (int i = 0; i < 3; ++i) {
        temp1[i] = upper_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        upper_[i][0] = temp2[i];
    }

    for (int i = 0; i < 3; ++i) {
        front_[i][0] = temp1[i];
    }

    rotate_matrix_to_right(left_);

    print();
}

void cube::rotate_front_to_right() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    for (int i = 0; i < 3; ++i) {
        temp1[i] = right_[2 - i][0];
    }
    for (int i = 0; i < 3; ++i) {
        right_[i][0] = upper_[2][i];
    }

    temp2 = lower_[0];
    lower_[0] = temp1;

    for (int i = 0; i < 3; ++i) {
        temp1[i] = left_[2 - i][2];
    }
    for (int i = 0; i < 3; ++i) {
        left_[i][2] = temp2[i];
    }

    upper_[2] = temp1;

    rotate_matrix_to_right(front_);

    print();
}

void cube::rotate_front_to_left() {
    counter_++;
    std::vector<color> temp1(3, stuff_c), temp2(3, stuff_c);

    for (int i = 0; i < 3; ++i) {
        temp1[i] = left_[i][2];
    }
    for (int i = 0; i < 3; ++i) {
        left_[i][2] = upper_[2][2 - i];
    }

    temp2 = lower_[0];
    lower_[0] = temp1;

    for (int i = 0; i < 3; ++i) {
        temp1[i] = right_[i][0];
    }
    for (int i = 0; i < 3; ++i) {
        right_[i][0] = temp2[2 - i];
    }

    upper_[2] = temp1;

    rotate_matrix_to_left(front_);

    print();
}

void cube::rotate_cube_to_right() {
    counter_++;
    std::vector<std::vector<color>> temp1, temp2;

    temp1 = right_;
    right_ = front_;

    temp2 = back_;
    back_ = temp1;

    temp1 = left_;
    left_ = temp2;

    front_ = temp1;

    rotate_matrix_to_left(upper_);
    rotate_matrix_to_right(lower_);

    print();
}

void cube::rotate_cube_to_left() {
    std::vector<std::vector<color>> temp1, temp2;

    temp1 = left_;
    left_ = front_;

    temp2 = back_;
    back_ = temp1;

    temp1 = right_;
    right_ = temp2;

    front_ = temp1;

    rotate_matrix_to_right(upper_);
    rotate_matrix_to_left(lower_);

    print();
}

void cube::rotate_cube_to_up() {
    std::vector<std::vector<color>> temp1, temp2;

    temp1 = upper_;
    upper_ = front_;

    temp2 = back_;
    back_ = temp1;
    rotate_matrix_to_left(back_);
    rotate_matrix_to_left(back_);

    temp1 = lower_;
    lower_ = temp2;
    rotate_matrix_to_right(lower_);
    rotate_matrix_to_right(lower_);

    front_ = temp1;

    rotate_matrix_to_right(right_);
    rotate_matrix_to_left(left_);

    print();
}

void cube::rotate_cube_to_down() {
    std::vector<std::vector<color>> temp1, temp2;

    temp1 = lower_;
    lower_ = front_;

    temp2 = back_;
    back_ = temp1;
    rotate_matrix_to_left(back_);
    rotate_matrix_to_left(back_);

    temp1 = upper_;
    upper_ = temp2;
    rotate_matrix_to_right(upper_);
    rotate_matrix_to_right(upper_);

    front_ = temp1;

    rotate_matrix_to_right(left_);
    rotate_matrix_to_left(right_);

    print();
}

std::vector<std::vector<color>>& cube::get_upper() {
    return upper_;
}

std::vector<std::vector<color>>& cube::get_lower() {
    return lower_;
}

std::vector<std::vector<color>>& cube::get_front() {
    return front_;
}

std::vector<std::vector<color>>& cube::get_left() {
    return left_;
}

std::vector<std::vector<color>>& cube::get_back() {
    return back_;
}

std::vector<std::vector<color>>& cube::get_right() {
    return right_;
}

void cube::print() {
    std::cout << " ";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << upper_[i][j] << " ";
        }
        std::cout << "\n ";
    }

    std::cout << "\r-------\n ";

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << front_[i][j] << " ";
        }

        std::cout << "| ";

        for (int j = 0; j < 3; ++j) {
            std::cout << right_[i][j] << " ";
        }

        std::cout << "| ";

        for (int j = 0; j < 3; ++j) {
            std::cout << back_[i][j] << " ";
        }

        std::cout << "| ";

        for (int j = 0; j < 3; ++j) {
            std::cout << left_[i][j] << " ";
        }

        std::cout << "\n ";
    }

    std::cout << "\r-------\n ";

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << lower_[i][j] << " ";
        }
        std::cout << "\n ";
    }
    std::cout << "Step: " + std::to_string(counter_) + "\n\n\n\n\n\n";
}