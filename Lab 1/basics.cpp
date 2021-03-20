#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include "basics.h"

point::point() : x_(0.0), y_(0.0) {}

point::point(double x, double y) : x_(x), y_(y) {}

point::point(const point &data) = default;

void point::setPoint(double x, double y) {
    x_ = x;
    y_ = y;
}

double point::getX() const {
    return x_;
}

double point::getY() const {
    return y_;
}

void point::printPoint() const {
    std::cout << "[" << x_ << ", " << y_ << "]\n";
}

double point::distance(const point &a, const point &b) {
    return sqrt(pow(a.x_ - b.x_, 2) + pow(a.y_ - b.y_, 2));
}

line::line(const point &a, const point &b) : a_(b.getY() - a.getY()),
                                             b_(-(b.getX() - a.getX())), c_(-(b.getX() * a_ + b.getY() * b_)) {}

void line::getLine() const {
    std::cout << a_ << "x";
    if (b_ > 0) {
        std::cout << "+" << b_ << "y";
    }
    else if (b_ < 0) {
        std::cout << b_ << "y";
    }
    if (c_ > 0) {
        std::cout << "+" << c_ << "\n";
    }
    else if (c_ < 0) {
        std::cout << c_ << "\n";
    }

}

int line::side(const point &data) const{
    double value = a_ * data.getX() + b_ * data.getY() + c_;
    if (value > 0) {
        return 1;
    }
    if (value < 0) {
        return -1;
    }
    return 0;
}

bool line::checkParallel(const line &l1, const line &l2) {
    double divider;
    if (std::abs(l1.a_) > 0.000001 && std::abs(l2.a_) > 0.000001) {
        divider = std::max(l1.a_, l2.a_) / std::min(l1.a_, l2.a_);
    }
    else {
        if (std::abs(l1.a_ - l2.a_) > 0.000001) {
            return false;
        }
        else {
            return true;
        }
    }
    if (std::abs(l1.b_) > 0.000001 && std::abs(l2.b_) > 0.000001) {
        if (std::abs(std::max(l1.b_, l2.b_) / std::min(l1.b_, l2.b_) - divider) > 0.000001) {
            return false;
        }
    }
    else {
        if (std::abs(l1.b_ - l2.b_) > 0.000001) {
            return false;
        }
    }
    return true;
}

polyline::polyline(const std::vector <point> &data) : points_(data) {
    if (data.empty()) {
        throw std::logic_error("Array is empty!");
    }
}

polyline::polyline() : points_() {}

double polyline::perimeter() const {
    double sum = 0;
    for (int i = 1; i < points_.size(); ++i) {
        sum += point::distance(points_[i - 1], points_[i]);
    }
    return sum;
}

void polyline::add(const point &x) {
    points_.push_back(x);
}

std::vector <point> polyline::getPoints() const {
    return points_;
}

point polyline::getThatPoint(int number) const {
    return points_[number - 1];
}

size_t polyline::getSize() const {
    return points_.size();
}

void polyline::addFirstPoint() {
    points_.push_back(points_[0]);
}

completePolyline::completePolyline(const std::vector <point> &data) : polyline_(data) {
    polyline_.addFirstPoint();
    checks::checkLessVertexes(data, 3);
}

completePolyline::completePolyline(const polyline &data) : polyline_(data){
    polyline_.addFirstPoint();
    if (data.getSize() < 3) {
        throw std::logic_error("Under 3 vertexes!");
    }
}

size_t completePolyline::getSize() const {
    return polyline_.getSize() - 1;
}

point completePolyline::getThatPoint(int number) const {
    return polyline_.getThatPoint(number);
}

std::vector <point> completePolyline::getPoints() const {
    std::vector <point> arr = polyline_.getPoints();
    arr.pop_back();
    return arr;
}

double completePolyline::perimeter() const {
    return polyline_.perimeter();
}

void checks::checkLessVertexes(const std::vector <point> &data, int n) {
    if (data.size() < n) {
        throw std::logic_error("Under " + std::to_string(n) + " vertexes!");
    }
}

void checks::checkNumberVertexes(const std::vector <point> &data, int n) {
    if (data.size() != n) {
        std::cout << "Only " << n << " points!";
        throw std::logic_error("Only " + std::to_string(n) + " points!");
    }
}

void checks::checkConvex(const completePolyline &data) {
    for (int i = 1; i < data.getSize() + 1; ++i) {
        line temp(data.getThatPoint(i), data.getThatPoint(i + 1));
        int counterOfZero = 0, counterOfOther = 0;
        for (int j = 1; j < data.getSize() + 1; ++j) {
            int side = temp.side(data.getThatPoint(j));
            if (side == 0) {
                counterOfZero++;
            }
            counterOfOther += side;
        }
        if (data.getSize() - counterOfZero != std::abs(counterOfOther) || data.getSize() == counterOfZero) {
            std::cout << "Not convex polygon!";
            exit(1);
        }
    }
}