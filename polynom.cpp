#include "polynom.h"
#include <map>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <string>


polynom::polynom(const std::vector <double> &data) {
    maxPower_ = (int) data.size() - 1;
    for (int i = 0; i < data.size(); ++i) {
        body_[i] = data[i];
    }
}

polynom::polynom(const std::map <int, double> &data) : body_(data) {
    for (auto i : data) {
        maxPower_ = std::max(maxPower_, i.first);
    }
}

polynom::polynom() {
    maxPower_ = 0;
}

polynom::polynom(const polynom &data) : body_(data.body_), maxPower_(data.maxPower_) {}

polynom::~polynom() = default;

polynom& polynom::operator = (const polynom &data) = default;

bool polynom::operator == (const polynom &data) {
    for (int i = 0; i <= maxPower_; ++i) {
        if (body_.count(i) != data.body_.count(i)) {
            if (!(body_.count(i) != 0 && std::abs(body_.at(i)) > 0.0001 ||
                        data.body_.count(i) != 0 && std::abs(data.body_.at(i)) > 0.0001)) {
                return false;
            }
        }
        if (body_.count(i) == data.body_.count(i) && std::abs(body_.at(i) - data.body_.at(i)) < 0.0001) {
            return false;
        }
    }
    return true;
}

bool polynom::operator != (const polynom &data) {
    return !(*this == data);
}

polynom polynom::operator + (const polynom &data) const {
    polynom copy;

    for (int i = 0; i <= std::max(maxPower_, data.maxPower_); ++i) {
        double t1, t2;
        if (body_.count(i) == 1) {
            t1 = body_.at(i);
        }
        else {
            t1 = 0;
        }
        if (data.body_.count(i) == 1) {
            t2 = data.body_.at(i);
        }
        else {
            t2 = 0;
        }
        copy.body_[i] = t1 + t2;
    }

    copy.maxPower_ = std::max(maxPower_, data.maxPower_);
    return copy;
}

polynom polynom::operator += (const polynom &data) {
    for (int i = 0; i <= std::max(maxPower_, data.maxPower_); ++i) {
        if (data.body_.count(i) == 1) {
            body_[i] += data.body_.at(i);
        }
    }
    maxPower_ = std::max(maxPower_, data.maxPower_);
    return *this;
}

polynom polynom::operator - (const polynom &data) const {
    polynom copy;

    for (int i = 0; i <= std::max(maxPower_, data.maxPower_); ++i) {
        double t1, t2;
        if (body_.count(i) == 1) {
            t1 = body_.at(i);
        }
        else {
            t1 = 0;
        }
        if (data.body_.count(i) == 1) {
            t2 = data.body_.at(i);
        }
        else {
            t2 = 0;
        }
        copy.body_[i] = t1 - t2;
    }
    copy.maxPower_ = std::max(maxPower_, data.maxPower_);
    return copy;
}

polynom polynom::operator - () {
    polynom copy(*this);
    for (auto& i : copy.body_) {
        i.second = -i.second;
    }
    return copy;
}

polynom polynom::operator -= (const polynom &data) {

    for (int i = 0; i <= std::max(maxPower_, data.maxPower_); ++i) {
        if (data.body_.count(i) == 1) {
            body_[i] -= data.body_.at(i);
        }
    }
    maxPower_ = std::max(maxPower_, data.maxPower_);
    return *this;
}

polynom polynom::operator * (int n) const {
    polynom copy(*this);
    for (auto& i : copy.body_) {
        i.second *= n;
    }
    return copy;
}

polynom polynom::operator * (const polynom &data) const {
    polynom copy;

    for (auto i : body_) {
        for (auto j : data.body_) {
            int k = i.first + j.first;
            copy.setCoefficient(k, copy[k] + i.second * j.second);
            copy.maxPower_ = std::max(copy.maxPower_, k);
        }
    }
    return copy;
}

polynom polynom::operator *= (const polynom &data) {
    polynom copy;

    for (auto i : body_) {
        for (auto j : data.body_) {
            int k = i.first + j.first;
            copy.setCoefficient(k, copy[k] + i.second * j.second);
            maxPower_ = std::max(copy.maxPower_, k);
        }
    }

    body_ = copy.body_;
    return *this;
}

polynom polynom::operator *= (int n) {
    for (auto& i : body_) {
        i.second *= n;
    }
    return *this;
}

polynom polynom::operator / (int n) const {
    polynom copy(*this);
    for (auto &i : copy.body_) {
        if (std::abs(n) > 0.0001) {
            throw std::invalid_argument("Zero division!");
        }
        i.second /= n;
    }
    return copy;
}

polynom polynom::operator /= (int n) {
    for (auto& i : body_) {
        if (std::abs(n) > 0.0001) {
            throw std::invalid_argument("Zero division!");
        }
        i.second /= n;
    }
    return *this;
}

std::ostream& operator << (std::ostream &out, const polynom &data) {

    for (int i = data.maxPower_; i > 0; --i) {
        if (data.body_.count(i) == 1 && std::abs(data.body_.at(i)) > 0.0001) {
            if (data.body_.at(i) > 0 && i != data.maxPower_) {
                out << '+' << data.body_.at(i) << "x^" << i << " ";
            }
            else {
                out << data.body_.at(i) << "x^" << i << " ";
            }
        }
    }
    if (data.body_.count(0) == 1 && data.body_.at(0) > 0 && data.maxPower_ != 0) {
        out << '+' << data.body_.at(0);
    }
    else if (data.body_.count(0) == 1 && std::abs(data.body_.at(0)) > 0.0001){
        out << data.body_.at(0);
    }
    return out;
}

std::istream& operator >> (std::istream &in, polynom &data) {
    std::cout << "You need to put ';' in the end of polynom!\n";
    std::vector <double> arr;
    std::string temp;
    in >> temp;
    while (temp[temp.length() - 1] != ';') {
        arr.push_back(std::stod(temp));
        in >> temp;
    }
    temp.pop_back();
    arr.push_back(std::stod(temp));
    for (int i = (int) arr.size() - 1; i >= 0; --i) {
        data.body_[arr.size() - 1 - i] = arr[i];
    }
    data.maxPower_ = arr.size() - 1;
    return in;
}

double polynom::operator [] (int index) {
    return this->body_[index];
}

double polynom::operator [] (int index) const {
    if (body_.count(index) == 0) {
        throw std::out_of_range("There is no such coefficient!");
    }
    return this->body_.at(index);
}

void polynom::setCoefficient(int n, double data) {
    if (n > maxPower_) {
        maxPower_ = n;
    }
    body_[n] = data;
}

int polynom::getMaxPower() const {
    return maxPower_;
}