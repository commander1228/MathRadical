#include <catch2/catch_test_macros.hpp>
#include "../Math/Fraction.h" // Includes the class being tested

// =============================================================================
// FRACTION CLASS TESTS
// =============================================================================

TEST_CASE("Fraction - Simplification and Normalization", "[Fraction][constructor]") {
    // Test 1: Basic Simplification (assuming it's implemented)
    Fraction f_simp(10, 20);
    REQUIRE(f_simp.getNumerator() == 1);
    REQUIRE(f_simp.getDenominator() == 2); 

    // Test 2: Negative Denominator (should normalize sign to numerator)
    Fraction f_neg(5, -10);
    REQUIRE(f_neg.getNumerator() == -1);
    REQUIRE(f_neg.getDenominator() == 2);
    
    // Test 3: Division by Zero
    REQUIRE_THROWS_AS(Fraction(5, 0), std::invalid_argument);
}

TEST_CASE("Fraction - Arithmetic Operators", "[Fraction][operators]") {
    Fraction a(1, 4);
    Fraction b(1, 3);
    
    // Test 4: Addition (1/4 + 1/3 = 7/12)
    Fraction sum = a + b;
    REQUIRE(sum.getNumerator() == 7);
    REQUIRE(sum.getDenominator() == 12);
    
    // Test 5: Multiplication (1/4 * 1/3 = 1/12)
    Fraction prod = a * b;
    REQUIRE(prod.getNumerator() == 1);
    REQUIRE(prod.getDenominator() == 12);
}

TEST_CASE("Fraction - Long Long Overflow Check", "[Fraction][long_long]") {
    // Uses numbers that would cause an INT overflow during common denominator calculation
    const long long LARGE_VAL = 2000000000LL; 
    
    Fraction f1(1, LARGE_VAL);
    Fraction f2(1, LARGE_VAL + 1);

    // Addition creates a common denominator > 4e18.
    Fraction f_sum = f1 + f2;
    
    // Check that the resulting denominator is larger than the maximum 32-bit signed integer
    REQUIRE(f_sum.getDenominator() > 2147483647LL);
}