#include <iostream>
#include "polynom.h"

int main() {
    std::vector<double> arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    polynom a(arr);
    polynom b;
    b.setCoefficient(3, 2);
    b.setCoefficient(1, 5);
    a *= b;
    std::cin >> b;
    std::cout << b << "\n";
    std::cout << a;
    return 0;
}