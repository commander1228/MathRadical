#include "MathUtils.h"
#include <cmath>
#include <iterator>
#include <algorithm>

int MathUtils::GCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int MathUtils::GCD(int a, int b, bool print) {
    int gcd = GCD(a, b);
    if (print)
        std::cout << "The greatest common denominator of " << a << " and " << b << " is " << gcd << std::endl;
    return gcd;
}

int MathUtils::LCM(int a, int b) {
    int gcd = GCD(a, b);
    return (a / gcd) * b;
}

int MathUtils::LCM(int a, int b, bool print) {
    int lcm = LCM(a, b);
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
