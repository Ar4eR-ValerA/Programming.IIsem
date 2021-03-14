#include <iostream>
#include <vector>
#include "basics.h"
#include "figures.h"

int main() {


    std::vector <point> arr(2);
    arr[0] = point(1, 1);
    arr[1] = point(2, 2);

    try {
        triangle a(arr);
    }
    catch (std::exception e) {
        arr.push_back({1, 2});
    }
    triangle a(arr);
    std::cout << a.space();

    return 0;
}
