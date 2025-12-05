#include "Fraction.h"
#include <stdexcept>
#include <cmath>
#include "MathUtils.h"
namespace RadMath {
    //constructor
    void Fraction::simplify() {

        if (numerator == 0) {
            denominator = 1;
            return;
        }

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        long long common = MathUtils::GCD(numerator, denominator);

        numerator /= common;
        denominator /= common;
    }

    Fraction::Fraction(long long num, long long den)
        : numerator(num), denominator(den)
    {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        simplify();
    }

    //operator overloads

    Fraction& Fraction::operator+=(const Fraction& other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator = denominator * other.denominator;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator-=(const Fraction& other) {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator = denominator * other.denominator;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator*=(const Fraction& other) {
        numerator *= other.numerator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator/=(const Fraction& other) {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero fraction is undefined.");
        }
        numerator *= other.denominator;
        denominator *= other.numerator;
        simplify();
        return *this;
    }



    Fraction operator+(const Fraction& a, const Fraction& b) {
        Fraction result = a;
        result += b;
        return result;
    }

    Fraction operator-(const Fraction& a, const Fraction& b) {
        Fraction result = a;
        result -= b;
        return result;
    }

    Fraction operator*(const Fraction& a, const Fraction& b) {
        Fraction result = a;
        result *= b;
        return result;
    }

    Fraction operator/(const Fraction& a, const Fraction& b) {
        Fraction result = a;
        result /= b;
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.numerator;
        if (f.denominator != 1) {
            os << "/" << f.denominator;
        }
        return os;
    }
}