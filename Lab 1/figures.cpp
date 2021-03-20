#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "figures.h"

polygon::polygon(const std::vector <point> &data) : body_(completePolyline(data)) {
    checks::checkLessVertexes(data, 3);
    checks::checkConvex(body_);
}

double polygon::space() const {
    double determinant = 0;
    for (int i = 1; i < body_.getSize() + 1; ++i) {
        determinant += body_.getThatPoint(i).getX() * body_.getThatPoint(i + 1).getY();
        determinant -= body_.getThatPoint(i).getY() * body_.getThatPoint(i + 1).getX();
    }
    return 0.5 * std::abs(determinant);
}

std::vector <point> polygon::getPoints() const {
    return body_.getPoints();
}

double polygon::perimeter() const {
    return body_.perimeter();
}

point polygon::getThatPoint(int number) const {
    return body_.getThatPoint(number);
}

size_t polygon::numberOfVertexes() const {
    return body_.getSize();
}

std::vector <point> polygon::getVertexes() const {
    return body_.getPoints();
}

triangle::triangle(const std::vector<point> &data) {
    body_ = completePolyline(data);
    checks::checkNumberVertexes(data, 3);
    checks::checkConvex(body_);
}

double triangle::space() const {
    point A = body_.getThatPoint(1);
    point B = body_.getThatPoint(2);
    point C = body_.getThatPoint(3);

    double a = point::distance(B, C);
    double b = point::distance(A, C);
    double c = point::distance(A, B);
    double p = (a + b + c) / 2;

    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

trapezoid::trapezoid(const std::vector<point> &data) {
    body_ = completePolyline(data);
    checks::checkNumberVertexes(data, 4);
    checks::checkConvex(body_);

    line l1(data[0], data[1]);
    line l2(data[1], data[2]);
    line l3(data[2], data[3]);
    line l4(data[3], data[0]);
    if (line::checkParallel(l1, l3) + line::checkParallel(l2, l4) != 1) {
        throw std::logic_error("Not a trapezoid");
    }
}

regularPolygon::regularPolygon(const std::vector<point> &data) {
    body_ = completePolyline(data);
    checks::checkConvex(body_);

    sideLength_ = point::distance(body_.getThatPoint(1), body_.getThatPoint(2));
    for (int i = 2; i < body_.getSize() + 1; ++i) {
        double temp = point::distance(body_.getThatPoint(i), body_.getThatPoint(i + 1));
        if (std::abs(sideLength_ - temp) > 0.001) {
            throw std::logic_error("Not a regular polygon");
        }
    }
}

double regularPolygon::space() const {
    int n = body_.getSize();
    double a = sideLength_;
    return (n * a * a) / (4 * std::tan(3.14159265 / n));
}

double regularPolygon::getSideLength() const{
    return sideLength_;
}