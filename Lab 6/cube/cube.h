#ifndef LAB_6_CUBE_H
#define LAB_6_CUBE_H
#include <vector>
#include "color.h"

class cube {
private:
    std::vector<std::vector<color>> front_, left_, back_, right_, lower_, upper_;
    int counter_ = 0;

    static void rotate_matrix_to_right(std::vector<std::vector<color>>& matrix);

    static void rotate_matrix_to_left(std::vector<std::vector<color>>& matrix);

public:
    cube();

    ~cube();

    static void enter_matrix(std::vector<std::vector<color>>& matrix);

    void init_front(const std::vector<std::vector<color>>& side);

    void init_left(const std::vector<std::vector<color>>& side);

    void init_back(const std::vector<std::vector<color>>& side);

    void init_right(const std::vector<std::vector<color>>& side);

    void init_upper(const std::vector<std::vector<color>>& side);

    void init_lower(const std::vector<std::vector<color>>& side);

    void rotate_lower_to_right();

    void rotate_lower_to_left();

    void rotate_upper_to_right();

    void rotate_upper_to_left();

    void rotate_right_to_up();

    void rotate_right_to_down();

    void rotate_left_to_up();

    void rotate_left_to_down();

    void rotate_front_to_right();

    void rotate_front_to_left();

    void rotate_cube_to_right();

    void rotate_cube_to_left();

    void rotate_cube_to_up();

    void rotate_cube_to_down();

    std::vector<std::vector<color>>& get_upper();

    std::vector<std::vector<color>>& get_lower();

    std::vector<std::vector<color>>& get_front();

    std::vector<std::vector<color>>& get_left();

    std::vector<std::vector<color>>& get_back();

    std::vector<std::vector<color>>& get_right();

    void print();
};

#endif //LAB_6_CUBE_H