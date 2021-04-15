#ifndef LAB_4_ALGS_H
#define LAB_4_ALGS_H


class algs {
public:
    template<class InputIterator, class UnaryPredicate>
    bool static all_of(InputIterator begin, InputIterator end, UnaryPredicate func);

    template<class InputIterator, class UnaryPredicate>
    bool static any_of(InputIterator begin, InputIterator end, UnaryPredicate func);

    template<class InputIterator, class UnaryPredicate>
    bool static none_of(InputIterator begin, InputIterator end, UnaryPredicate func);

    template<class InputIterator, class UnaryPredicate>
    bool static one_of(InputIterator begin, InputIterator end, UnaryPredicate func);

    template<class InputIterator, class BinaryPredicate>
    bool static is_sorted(InputIterator begin, InputIterator end, BinaryPredicate func);

    template<class InputIterator, class UnaryPredicate>
    bool static is_partitioned(InputIterator begin, InputIterator end, UnaryPredicate func);

    template<class InputIterator, class Type>
    InputIterator static find_not(InputIterator begin, InputIterator end, const Type& value);

    template<class InputIterator, class Type>
    InputIterator static find_backward(InputIterator begin, InputIterator end, const Type& value);

    template<class InputIterator, class UnaryPredicate>
    bool static is_palindrome(InputIterator begin, InputIterator end, UnaryPredicate func);
};


#endif //LAB_4_ALGS_H
