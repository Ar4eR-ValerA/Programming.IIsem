#include <iostream>
#include <algorithm>
#include "circular_buffer.h"

int main() {
    circular_buffer<int> a(3);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(5);

    for (int i : a) {
        std::cout << i << " ";
    }

    std::sort(a.begin(), a.end());

    std::cout << a[5];
    return 0;
}
