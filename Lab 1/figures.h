#ifndef LAB_1_FIGURES_H
#define LAB_1_FIGURES_H
#include "basics.h"


class polygon {
protected:
    completePolyline body_;

public:

    explicit polygon(const std::vector <point> &data);

    polygon() = default;

    polygon(const polygon &data) = default;

    polygon &operator = (const polygon &data) = default;

    virtual double space() const;

    double perimeter() const;

    std::vector <point> getPoints() const;

    point getThatPoint(int number) const;

    size_t numberOfVertexes() const;

    std::vector <point> getVertexes() const;
};

class triangle: public polygon {
public:
    explicit triangle(const std::vector<point> &data);

    triangle(const triangle &data) = default;

    double space() const override;

    triangle &operator = (const triangle &data) = default;
};

class trapezoid: public polygon {
public:
    explicit trapezoid(const std::vector<point> &data);

    trapezoid(const trapezoid &data) = default;

    trapezoid &operator = (const trapezoid &data) = default;
};

class regularPolygon: public polygon {
private:
    double sideLength_;
public:
    explicit regularPolygon(const std::vector<point> &data);

    double getSideLength() const;

    regularPolygon(const regularPolygon &data) = default;

    double space() const override;

    regularPolygon &operator = (const regularPolygon &data) = default;
};

#endif //LAB_1_FIGURES_H