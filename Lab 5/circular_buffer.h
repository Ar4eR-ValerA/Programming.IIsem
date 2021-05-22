#ifndef LAB_5_CIRCULAR_BUFFER_H
#define LAB_5_CIRCULAR_BUFFER_H
#include "iterator.h"

template<class value_type>
class circular_buffer {
public:
    using iterator = iterator_cb<value_type>;
    using diff_type = typename iterator_cb<value_type>::difference_type;
    friend iterator;

private:
    diff_type size_, capacity_;
    value_type* begin_;
    value_type* end_;
    value_type* first_;
    value_type* last_;

public:
    explicit circular_buffer(diff_type capacity = 0) : capacity_(capacity), size_(0) {
        begin_ = new value_type[capacity + 1];
        end_ = begin_ + capacity + 1;
        first_ = begin_ + 1;
        last_ = begin_ + 1;
    }

    circular_buffer(const circular_buffer& obj) : capacity_(obj.capacity_), size_(obj.size_) {
        begin_ = new value_type[obj.capacity_ + 1];
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
            throw std::logic_error("Capacity is zero!");
        }

        if (first_ == begin_) {
            first_ = end_;
        }
        if (last_ == first_ - 1) {
            if (first_ == end_) {
                first_ = begin_ + 1;
            }
            else {
                first_++;
                if (first_ == end_) {
                    first_ = begin_;
                }
            }
        }

        *last_ = value;
        last_++;
        if (size_ != capacity_) {
            size_++;
        }

        if (last_ == end_) {
            last_ = begin_;
        }
    }

    void push_front(const value_type& value) {
        if (capacity_ == 0) {
            throw std::logic_error("Capacity is zero!");
        }

        if (first_ == begin_) {
            first_ = end_;
        }

        if (first_ - 1 == last_) {
            if (last_ == begin_) {
                last_ = end_;
            }
            last_--;
        }

        first_--;
        *first_ = value;
        if (size_ != capacity_) {
            size_++;
        }
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::logic_error("Capacity is zero!");
        }

        if (last_ == begin_) {
            last_ = end_;
        }
        last_--;

        size_--;
    }

    void pop_front() {
        if (size_ == 0) {
            throw std::logic_error("Capacity is zero!");
        }

        first_++;
        if (first_ == end_) {
            first_ = begin_;
        }
        size_--;
    }

    value_type& operator[](diff_type n) {
        if (size_ == 0) {
            throw std::out_of_range("Size is zero!");
        }
        n = n % size_;
        if (n > end_ - first_) {
            return *(first_ - (n - (end_ - begin_)));
        }
        else {
            return *(first_ + n);
        }
    }

    const value_type& operator[](diff_type n) const {
        if (size_ == 0) {
            throw std::out_of_range("Size is zero!");
        }
        n = n % size_;
        if (n > end_ - first_) {
            return *(first_ - (n - (end_ - begin_)));
        }
        else {
            return *(first_ + n);
        }
    }

    iterator begin() {
        if (size_ == 0) {
            return iterator();
        }
        return iterator(first_, first_, last_, begin_, end_, size_);
    }

    const iterator begin() const {
        if (size_ == 0) {
            return iterator();
        }
        return iterator(first_, first_, last_, begin_, end_, size_);
    }

    iterator end() {
        if (size_ == 0) {
            return iterator();
        }
        return iterator(last_, first_, last_, begin_, end_, size_);
    }

    const iterator end() const {
        if (size_ == 0) {
            return iterator();
        }
        return iterator(last_, first_, last_, begin_, end_, size_);
    }

    void set_capacity(diff_type n) {
        auto temp = new value_type[n];

        int i = 0;
        for (auto it = first_; (i == 0 || it != last_) && i < n; ++it, ++i) {
            if (it == end_) {
                it = begin_;
            }
            temp[i] = *it;
        }

        capacity_ = n;
        size_ = std::min(size_, n);
        delete[] begin_;

        begin_ = new value_type[capacity_ + 1];
        end_ = begin_ + capacity_ + 1;
        first_ = begin_ + 1;
        last_ = begin_ + size_ + 1;
        if (last_ == end_) {
            last_ = begin_;
        }

        i = 0;
        for (auto it = begin_ + 1; it != end_; ++it, ++i) {
            *it = temp[i];
        }
        delete[] temp;
    }
};

#endif //LAB_5_CIRCULAR_BUFFER_H