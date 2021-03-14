#ifndef LAB_1_BASICS_H
#define LAB_1_BASICS_H

class point {
private:
    double x_{}, y_{};

public:
    point();

    point(double x, double y);

    point(const point &data);

    point& operator = (const point &data) = default;

    void setPoint(double x, double y);

    double getX() const;

    double getY() const;

    void printPoint() const;

    static double distance(const point &a, const point &b);
};

class line {
private:
    double a_, b_, c_;

public:
    line(const point &a, const point &b);

    line &operator = (const line &data) = default;

    void getLine() const;

    int side(const point &data) const;

    static bool checkParallel(const line &l1, const line &l2);
};

class polyline {
private:
    std::vector <point> points_;

public:
    explicit polyline(const std::vector <point> &data) ;

    polyline(const polyline &data) = default;

    polyline();

    polyline &operator = (const polyline &data) = default;

    double perimeter() const;

    void add(const point &x);

    std::vector <point> getPoints() const;

    point getThatPoint(int number) const;

    size_t getSize() const;

    void addFirstPoint();
};

class completePolyline {
protected:
    polyline polyline_;
public:
    completePolyline() = default;

    explicit completePolyline(const std::vector <point> &data);

    explicit completePolyline(const polyline &data);

    size_t getSize() const;

    point getThatPoint(int number) const;

    std::vector <point> getPoints() const;

    completePolyline &operator = (const completePolyline &data) = default;

    double perimeter() const;
};

class checks {
public:
    static void checkLessVertexes(const std::vector<point> &data, int n);

    static void checkNumberVertexes(const std::vector<point> &data, int n);

    static void checkConvex(const completePolyline &data);
};

#endif //LAB_1_BASICS_H
