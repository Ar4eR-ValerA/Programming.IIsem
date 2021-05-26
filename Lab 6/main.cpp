#include <iostream>
#include <vector>
#include "cube/color.h"
#include "cube/cube.h"
#include "cube_algorithms.h"

int main() {
    cube a;
    std::vector<std::vector<color>> t(3, std::vector<color>(3, stuff_c));

    std::cout << "front:\n";
    cube::enter_matrix(t);
    a.init_front(t);

    std::cout << "right:\n";
    cube::enter_matrix(t);
    a.init_right(t);

    std::cout << "back:\n";
    cube::enter_matrix(t);
    a.init_back(t);

    std::cout << "left:\n";
    cube::enter_matrix(t);
    a.init_left(t);

    std::cout << "upper:\n";
    cube::enter_matrix(t);
    a.init_upper(t);

    std::cout << "lower:\n";
    cube::enter_matrix(t);
    a.init_lower(t);

    /*
        green blue red
        blue orange orange
        green blue green

        blue white orange
        white green yellow
        orange yellow red

        yellow red white
        red red blue
        blue red blue

        blue orange white
        orange blue yellow
        orange orange yellow

        orange green green
        yellow white green
        red white white

        red red white
        green yellow green
        yellow white yellow

     */

    /*t[0][0] = green;
    t[1][0] = blue;
    t[2][0] = green;
    t[0][1] = blue;
    t[1][1] = orange;
    t[2][1] = blue;
    t[0][2] = red;
    t[1][2] = orange;
    t[2][2] = green;
    a.init_front(t);

    t[0][0] = blue;
    t[1][0] = white;
    t[2][0] = orange;
    t[0][1] = white;
    t[1][1] = green;
    t[2][1] = yellow;
    t[0][2] = orange;
    t[1][2] = yellow;
    t[2][2] = red;
    a.init_right(t);

    t[0][0] = yellow;
    t[1][0] = red;
    t[2][0] = blue;
    t[0][1] = red;
    t[1][1] = red;
    t[2][1] = red;
    t[0][2] = white;
    t[1][2] = blue;
    t[2][2] = blue;
    a.init_back(t);

    t[0][0] = blue;
    t[1][0] = orange;
    t[2][0] = orange;
    t[0][1] = orange;
    t[1][1] = blue;
    t[2][1] = orange;
    t[0][2] = white;
    t[1][2] = yellow;
    t[2][2] = yellow;
    a.init_left(t);

    t[0][0] = orange;
    t[1][0] = yellow;
    t[2][0] = red;
    t[0][1] = green;
    t[1][1] = white;
    t[2][1] = white;
    t[0][2] = green;
    t[1][2] = green;
    t[2][2] = white;
    a.init_upper(t);

    t[0][0] = red;
    t[1][0] = green;
    t[2][0] = yellow;
    t[0][1] = red;
    t[1][1] = yellow;
    t[2][1] = white;
    t[0][2] = white;
    t[1][2] = green;
    t[2][2] = yellow;
    a.init_lower(t);*/


    cube_algorithms::assemble(a);
    return 0;
}
