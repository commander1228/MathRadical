#ifndef MATHRADICAL_FRACTION_H
#define MATHRADICAL_FRACTION_H

#include <iosfwd>


class Fraction {
private:
    long long numerator;
    long long denominator;
    void simplify();


public:

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

    Fraction(long long num = 0, long long den = 1);

    long long getNumerator() const {return numerator;};

    long long getDenominator() const {return denominator;};

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);
};

Fraction operator+(const Fraction& a, const Fraction& b);
Fraction operator-(const Fraction& a, const Fraction& b);
Fraction operator*(const Fraction& a, const Fraction& b);
Fraction operator/(const Fraction& a, const Fraction& b);


#endif //MATHRADICAL_FRACTION_H