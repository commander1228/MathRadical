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
};

#endif
