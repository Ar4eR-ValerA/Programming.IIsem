#ifndef LAB_5_ITERATOR_H
#define LAB_5_ITERATOR_H
#include <iterator>
#include "circular_buffer.h"


template<class value_type>
class iterator_cb : public std::iterator<std::random_access_iterator_tag, value_type> {
private:
    value_type* pointer_ = nullptr;
    value_type* first_ = nullptr;
    value_type* last_ = nullptr;
    value_type* begin_ = nullptr;
    value_type* end_ = nullptr;
    using diff_type = typename std::iterator<std::random_access_iterator_tag, value_type>::difference_type;
    diff_type size_ = 0;


public:
    iterator_cb() = default;

    ~iterator_cb() = default;

    explicit iterator_cb(value_type* ptr, value_type* first, value_type* last, value_type* begin, value_type* end, diff_type size) :
            pointer_(ptr),
            first_(first),
            last_(last),
            begin_(begin),
            end_(end),
            size_(size) {}

    iterator_cb& operator=(const iterator_cb& it) = default;

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
        if (pointer_ == end_) {
            pointer_ = begin_;
        }
        return *this;
    }

    iterator_cb operator++(int) {
        value_type prev = *this;
        ++(*this);
        return prev;
    }

    iterator_cb &operator--() {
        if (pointer_ == begin_) {
            pointer_ = end_;
        }
        --pointer_;
        return *this;
    }

    iterator_cb operator--(int) {
        value_type prev = *this;
        --(*this);
        return prev;
    }

    iterator_cb& operator+=(diff_type n) {
        n = n % size_;
        if (n > end_ - pointer_) {
            pointer_ -= end_ - begin_ - n;
        }
        else {
            pointer_ += n;
        }
        return *this;
    }

    iterator_cb operator+(diff_type n) {
        auto it = *this;
        return it += n;
    }

    iterator_cb& operator-=(diff_type n) {
        n = n % size_;
        if (n > pointer_ - begin_) {
            pointer_ += end_ - begin_ - n;
        }
        else {
            pointer_ -= n;
        }
        return *this;
    }

    iterator_cb operator-(diff_type n) {
        auto it = *this;
        return it -= n;
    }

    diff_type operator-(const iterator_cb& it) {
        return pointer_ - it.pointer_;
    }

    value_type& operator[](size_t n) {
        return *(this += n);
    }

    bool operator<(const iterator_cb &it) {
        if (pointer_ > first_ && it.pointer_ > first_ || pointer_ < first_ && it.pointer_ < first_) {
            return pointer_ < it.pointer_;
        }
        else {
            return pointer_ > it.pointer_;
        }
    }

    bool operator>(const iterator_cb &it) {
        if (pointer_ > first_ && it.pointer_ > first_ || pointer_ < first_ && it.pointer_ < first_) {
            return pointer_ > it.pointer_;
        }
        else {
            return pointer_ < it.pointer_;
        }
    }

    bool operator>=(const iterator_cb &it) {
        if (pointer_ > first_ && it.pointer_ > first_ || pointer_ < first_ && it.pointer_ < first_) {
            return pointer_ <= it.pointer_;
        }
        else {
            return pointer_ >= it.pointer_;
        }
    }

    bool operator<=(const iterator_cb &it) {
        if (pointer_ > first_ && it.pointer_ > first_ || pointer_ < first_ && it.pointer_ < first_) {
            return pointer_ >= it.pointer_;
        }
        else {
            return pointer_ <= it.pointer_;
        }
    }
};

#endif //LAB_5_ITERATOR_H
