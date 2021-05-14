#ifndef LAB_5_CIRCULAR_BUFFER_H
#define LAB_5_CIRCULAR_BUFFER_H
#include "iterator.h"

template<class value_type>
class circular_buffer {
public:
    using iterator = iterator_cb<value_type>;
    friend iterator;

private:
    size_t size_, capacity_;
    value_type* begin_;
    value_type* end_;
    value_type* first_;
    value_type* last_;

public:
    explicit circular_buffer(size_t capacity = 0) : capacity_(capacity), size_(0) {
        begin_ = new value_type(capacity);
        end_ = begin_ + capacity;
        first_ = begin_;
        last_ = begin_;
    }

    circular_buffer(circular_buffer& obj) : capacity_(obj.capacity_), size_(obj.size_) {
        begin_ = new value_type(obj.capacity_);
        end_ = begin_ + obj.capacity_;
        last_ = begin_;

        value_type* it = obj.first_, it_ = first_;
        for (;it != obj.last_; ++it, ++it_) {
            *it_ = *it;
        }
        last_ = it_;
    }

    ~circular_buffer() {
        delete[] begin_;
    }

    void push_back(const value_type& value) {
        if (capacity_ == 0) {
            return;
        }

        if (last_ == end_) {
            last_ = first_;
        }

        *last_ = value;
        last_++;
        if (size_ != capacity_) {
            size_++;
        }
    }

    void push_front(const value_type& value) {
        if (capacity_ == 0) {
            return;
        }

        if (first_ == begin_) {
            first_ = last_;
        }

        first_--;
        *first_ = value;
        if (size_ != capacity_) {
            size_++;
        }
    }

    void pop_back() {
        if (size_ == 0) {
            return;
        }

        last_--;

        if (last_ == first_) {
            first_++;
            if (first_ == end_) {
                first_ = begin_;
            }
        }

        if (last_ == begin_) {
            last_ = end_;
        }

        size_--;
    }

    void pop_front() {
        if (size_ == 0) {
            return;
        }

        first_++;

        if (first_ == last_) {
            last_--;
            if (last_ == begin_) {
                last_ = end_;
            }
        }

        if (first_ == end_) {
            first_ = begin_;
        }
        size_--;
    }

    value_type& operator[](size_t n) {
        return *(first_ + n % size_);
    }

    iterator begin() {
        if (size_ == 0) {
            return iterator();
        }
        return iterator(first_);
    }

    iterator end() {
        if (size_ == 0) {
            return iterator();
        }
        if (size_ == capacity_) {
            return iterator(end_);
        }
        else {
            return iterator(last_);
        }
    }
};

#endif //LAB_5_CIRCULAR_BUFFER_H