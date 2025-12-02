#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../Math/MathUtils.h" // Includes the class being tested

using namespace Catch::Matchers;

// =============================================================================
// MATHUTILS TESTS (GCD, LCM, isPrime, slope)
// =============================================================================

TEST_CASE("MathUtils - GCD and LCM Stability", "[MathUtils][long_long]") {
    // Test 1: Standard GCD
    REQUIRE(MathUtils::GCD(150, 225) == 75);

    // Test 2: GCD with large numbers, checking long long support
    long long g2_a = 2147483600LL;
    long long g2_b = 1000000100LL;
    REQUIRE(MathUtils::GCD(g2_a, g2_b) == 100LL);

    // Test 3: Standard LCM
    REQUIRE(MathUtils::LCM(12, 18) == 36);

    // Test 4: LCM resulting in a large number (Overflow Check: > 32-bit max)
    long long l4_a = 2147483647LL; 
    long long l4_b = 2LL;
    REQUIRE(MathUtils::LCM(l4_a, l4_b) == 4294967294LL);
}

TEST_CASE("MathUtils - isPrime Checks", "[MathUtils][prime]") {
    // Test 5: Known Primes
    REQUIRE(MathUtils::isPrime(2) == true);
    REQUIRE(MathUtils::isPrime(17) == true);

    // Test 6: Known Non-Primes
    REQUIRE(MathUtils::isPrime(49) == false);

    // Test 7: Edge Cases
    REQUIRE(MathUtils::isPrime(1) == false);
    REQUIRE(MathUtils::isPrime(-5) == false);
}

TEST_CASE("MathUtils - Slope Calculations", "[MathUtils][slope]") {
    // Test 8: Positive slope
    REQUIRE_THAT(MathUtils::slope(2.0, 1.0, 4.0, 5.0), WithinAbs(2.0, 0.0001));

    // Test 9: Slope using arrays
    double p1[] = {1.0, 3.0};
    double p2[] = {3.0, 7.0};
    REQUIRE_THAT(MathUtils::slope(p1, p2), WithinAbs(2.0, 0.0001));

    // Test 10: Vertical line (x1 = x2) - Expects exception
    double p3[] = {1.0, 1.0};
    double p4[] = {1.0, 5.0};
    REQUIRE_THROWS_AS(MathUtils::slope(p3, p4), std::runtime_error);
}