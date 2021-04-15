#include "algs.h"

template<class InputIterator, class UnaryPredicate>
bool algs::all_of(InputIterator begin, InputIterator end, UnaryPredicate func) {
    for (auto i = begin; i != end; ++i) {
        if (!func(*i)) {
            return false;
        }
    }
    return true;
}

template<class InputIterator, class UnaryPredicate>
bool algs::any_of(InputIterator begin, InputIterator end, UnaryPredicate func) {
    for (auto i = begin; i != end; ++i) {
        if (func(*i)) {
            return true;
        }
    }
    return false;
}

template<class InputIterator, class UnaryPredicate>
bool algs::none_of(InputIterator begin, InputIterator end, UnaryPredicate func) {
    return !(algs::any_of(begin, end, func));
}

template<class InputIterator, class UnaryPredicate>
bool algs::one_of(InputIterator begin, InputIterator end, UnaryPredicate func) {
    int count = 0;
    for (auto i = begin; i != end; ++i) {
        if (func(*i)) {
            ++count;
        }
    }

    if (count == 1) {
        return true;
    }
    else {
        return false;
    }
}

template<class InputIterator, class BinaryPredicate>
bool algs::is_sorted(InputIterator begin, InputIterator end, BinaryPredicate func) {
    for (auto i = begin + 1; i != end; ++i) {
        if (!func(*(i - 1), *i)) {
            return false;
        }
    }
    return true;
}

template<class InputIterator, class UnaryPredicate>
bool algs::is_partitioned(InputIterator begin, InputIterator end, UnaryPredicate func) {
    bool fl = func(*begin);

    InputIterator i;
    for (i = begin + 1; i != end; ++i) {
        if (func(*i) != fl) {
            fl = !fl;
            ++i;
            break;
        }
    }
    if (i == end) {
        return false;
    }

    for (; i != end; ++i) {
        if (func(*i) != fl) {
            return false;
        }
    }
    return true;
}

template<class InputIterator, class Type>
InputIterator algs::find_not(InputIterator begin, InputIterator end, const Type& value) {
    for (auto i = begin; i != end; ++i) {
        if (*i != value) {
            return i;
        }
    }
    return end;
}

template<class InputIterator, class Type>
InputIterator algs::find_backward(InputIterator begin, InputIterator end, const Type& value) {
    for (auto i = end - 1; i != begin; --i) {
        if (*i == value) {
            return i;
        }
    }

    if (*begin == value) {
        return begin;
    }
    else {
        return end;
    }
}

template<class InputIterator, class UnaryPredicate>
bool algs::is_palindrome(InputIterator begin, InputIterator end, UnaryPredicate func) {
    for (auto i = begin, j = end - 1; i != end; ++i, --j) {
        if (func(*i) != func(*j)) {
            return false;
        }
    }
    return true;
}