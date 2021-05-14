#ifndef LAB_5_ITERATOR_H
#define LAB_5_ITERATOR_H
#include <iterator>


template<class value_type>
class iterator_cb : public std::iterator<std::random_access_iterator_tag, value_type> {
private:
    value_type* pointer_;
    using diff_type = typename std::iterator<std::random_access_iterator_tag, value_type>::difference_type;


public:
    iterator_cb() : pointer_(0) {}

    ~iterator_cb() = default;

    explicit iterator_cb(value_type* ptr) : pointer_(ptr) {}

    iterator_cb &operator=(const iterator_cb& it) = default;

    bool operator==(const iterator_cb& it) {
        return pointer_ == it.pointer_;
    }

    bool operator!=(const iterator_cb& it) {
        return pointer_ != it.pointer_;
    }

    value_type& operator*() {
        return *pointer_;
    }

    iterator_cb &operator++() {
        pointer_++;
        return *this;
    }

    iterator_cb operator++(int) {
        value_type prev = *this;
        (*this)++;
        return prev;
    }

    iterator_cb &operator--() {
        --pointer_;
        return *this;
    }

    iterator_cb operator--(int) {
        value_type prev = *this;
        (*this)--;
        return prev;
    }

    iterator_cb& operator+=(diff_type n) {
        pointer_ += n;
        return *this;
    }

    iterator_cb operator+(diff_type n) {
        auto it = *this;
        return it += n;
    }

    iterator_cb& operator-=(diff_type n) {
        pointer_ += n;
        return *this;
    }

    iterator_cb operator-(diff_type n) {
        auto it = *this;
        return it -= n;
    }

    diff_type operator-(const iterator_cb& it) {
        return pointer_ - it.pointer_;
    }

    value_type operator[](size_t n) {
        return pointer_[n];
    }

    bool operator<(const iterator_cb &it) {
        return pointer_ < it.pointer_;
    }

    bool operator>(const iterator_cb &it) {
        return pointer_ > it.pointer_;
    }

    bool operator>=(const iterator_cb &it) {
        return pointer_ >= it.pointer_;
    }

    bool operator<=(const iterator_cb &it) {
        return pointer_ <= it.pointer_;
    }
};

#endif //LAB_5_ITERATOR_H
