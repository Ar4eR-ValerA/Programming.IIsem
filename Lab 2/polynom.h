#ifndef LAB_2_POLYNOM_H
#define LAB_2_POLYNOM_H
#include <iostream>
#include <map>
#include <vector>

class polynom {
private:
    std::map <int, double> body_;

    int maxPower_;

public:
    explicit polynom(const std::vector <double> &data);

    explicit polynom(const std::map <int, double> &data);

    polynom();

    polynom(const polynom &data);

    ~polynom();

    polynom& operator = (const polynom &data);

    bool operator == (const polynom &data);

    bool operator != (const polynom &data);

    polynom operator + (const polynom &data) const;

    polynom operator += (const polynom &data);

    polynom operator - (const polynom &data) const;

    polynom operator - ();

    polynom operator -= (const polynom &data);

    polynom operator * (int n) const;

    polynom operator * (const polynom &data) const;

    polynom operator *= (int n);

    polynom operator *= (const polynom &data);

    polynom operator / (int n) const;

    polynom operator /= (int n);

    friend std::ostream& operator << (std::ostream &out, const polynom &data);

    friend std::istream& operator >> (std::istream &in, polynom &data);

    double operator [] (int index);

    double operator [] (int index) const;

    void setCoefficient(int n, double data);

    int getMaxPower() const;
};


#endif //LAB_2_POLYNOM_H
