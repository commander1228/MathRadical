#include "MathUtils.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

long long MathUtils::GCD(long long a, long long b) {
    a = std::llabs(a);
    b = std::llabs(b);

    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long MathUtils::GCD(long long a, long long b, bool print) {
    long long gcd = GCD(a, b);
    if (print)
        std::cout << "The greatest common divisor of " << a << " and " << b << " is " << gcd << std::endl;
    return gcd;
}

long long MathUtils::LCM(long long a, long long b) {
    long long gcd = MathUtils::GCD((long long)a, (long long)b);
    long long result = ((long long)a / gcd) * (long long)b;

    return result;
}

long long MathUtils::LCM(long long a, long long b, bool print) {
    long long lcm = LCM(a, b);
    if (print)
        std::cout << "The least common multiple of " << a << " and " << b << " is " << lcm << std::endl;
    return lcm;
}

bool MathUtils::isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

bool MathUtils::isPrime(int n, bool print) {
    bool result = isPrime(n);
    if (print) {
        if (result)
            std::cout << n << " is prime." << std::endl;
        else
            std::cout << n << " is not prime." << std::endl;
    }
    return result;
}

double MathUtils::slope(double a, double b, double c, double d) {
    double numerator = d - b;
    double denominator = c - a;

    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero: Vertical line (infinite slope)");
    }

    return numerator / denominator;
}

double MathUtils::slope(double a, double b, double c, double d, bool print) {
    double result = slope(a,b,c,d);
    if (print)
        std::cout<<"the slope between the points ("<< a << ","<< b <<
            ") and ("<<c<<","<<d<< ") is "<<result<<std::endl;
    return result;
}

double MathUtils::slope(double a[], double b[]) {
    double numerator = b[1] - a[1];
    double denominator = b[0] - a[0];

    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero: Vertical line (infinite slope)");
    }

    return numerator / denominator;
}

double MathUtils::slope(double a[], double b[], bool print) {
    double result = slope(a,b);
    if (print) {
        std::cout << "The slope between the points ("
                     << a[0] << "," << a[1] << ") and ("
                     << b[0] << "," << b[1] << ") is "
                     << result << std::endl;
    }
    return result;
}