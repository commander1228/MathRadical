#ifndef MATHRADICAL_MATHUTILS_H
#define MATHRADICAL_MATHUTILS_H

#include <iostream>

class MathUtils {
public:
    /**
      * Returns the greatest common denominator (GCD) of two integers.
      * @param a First integer
      * @param b Second integer
      * @param print If true, prints the result
      * @return GCD of a and b
      */
    static int GCD(int a, int b);
    static int GCD(int a, int b, bool print);

    /**
   * Returns the least common multiple (LCM) of two integers.
   * @param a First integer
   * @param b Second integer
   * @param print If true, prints the result
   * @return LCM of a and b
   */
    static int LCM(int a, int b);
    static int LCM(int a, int b, bool print);


    /**
    * Checks if a number is prime.
    * @param n The integer to check
    * @param print If true, prints the result
    * @return true if n is prime, false otherwise
    */
    static bool isPrime(int n);
    static bool isPrime(int n, bool print);

    /**
    * returns the slope fo two points
    * @param a x1
    * @param b = y1
    * @param c = x2
    * @param d = y2
    * @param print If true, prints the result
    * @return the slope of the two given points
    */
    static double slope(double a, double b, double c, double d);
    static double slope(double a, double b, double c, double d, bool print);

    /**
    * returns the slope fo two points
    * @param a an array with two values representing x and y
    * @param b the second array with two values representing x and y
    * @param print If true, prints the result
    * @return the slope of the two given points
    */
    static double slope(double a[], double b[]);
    static double slope(double a[], double b[], bool print);
};

#endif
