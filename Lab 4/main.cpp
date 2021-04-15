#include <iostream>
#include <vector>
#include "algs.cpp"

bool is_4(int x) {
    if (x == 4) {
        return true;
    }
    return false;
}

bool greater(int x, int y) {
    if (x < y) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    std::vector<int> a(20);

    for (int i = 0; i < 10; ++i) {
        a[i] = i * i;
    }
    for (int i = 10; i < 20; ++i) {
        a[i] = (19 - i) * (19 - i);
    }

    for (auto i : a) {
        std:: cout << i << " ";
    }
    std::cout << "\n";


    std::cout << "all_of: " << algs::all_of(a.begin(), a.end(), is_4) << "\n";

    std::cout << "any_of: " << algs::any_of(a.begin(), a.end(), is_4) << "\n";

    std::cout << "none_of: " << algs::none_of(a.begin(), a.end(), is_4) << "\n";

    std::cout << "one_of: " << algs::one_of(a.begin(), a.end(), is_4) << "\n";

    std::cout << "is_sorted: " << algs::is_sorted(a.begin(), a.end(), greater) << "\n";

    std::cout << "is_partitioned: " << algs::is_partitioned(a.begin(), a.end(), is_4) << "\n";

    std::cout << "find_not: " << *algs::find_not(a.begin(), a.end(), 5) << "\n";

    std::cout << "find_backward: " << *algs::find_backward(a.begin(), a.end(), 4) << "\n";

    std::cout << "is_palindrome: " << algs::is_palindrome(a.begin(), a.end(), is_4) << "\n";

    return 0;
}
