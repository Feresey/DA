#ifndef TCOMPLEX_HPP
#define TCOMPLEX_HPP
// #include <cmath>
// #include <iostream>

struct TComplex {
    double re, im;

    constexpr TComplex(double real = 0, double imag = 0)
        : re(real)
        , im(imag)
    {
    }
    constexpr TComplex& operator+=(const TComplex& rhs)
    {
        re += rhs.re;
        im += rhs.im;
        return *this;
    }
    constexpr TComplex& operator-=(const TComplex& rhs)
    {
        re -= rhs.re;
        im -= rhs.im;
        return *this;
    }

    friend constexpr TComplex operator+(const TComplex& lhs, const TComplex& rhs) { return TComplex(lhs) += rhs; }
    friend constexpr TComplex operator-(const TComplex& lhs, const TComplex& rhs) { return TComplex(lhs) -= rhs; }
    constexpr TComplex operator*(const TComplex& rhs) const { return { re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re }; }
    constexpr TComplex operator/(const int rhs) const { return { re / rhs, im / rhs }; }
    constexpr double Abs() const { return re * re + im * im; }
};

#endif
