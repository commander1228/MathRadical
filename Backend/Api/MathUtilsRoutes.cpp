#include <iostream>
#include <string>
#include <cstdint>
#include "MathUtilsRoutes.h"
#include "MathUtils.h"

MathUtilsRoutes::MathUtilsRoutes(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/gcd/<string>/<string>")
    ([&](const std::string& aStr, const std::string& bStr) {
      long long a = std::stoll(aStr);
      long long b = std::stoll(bStr);
      long long result = MathUtils::GCD(a,b);
      return std::to_string(result);
    });

    CROW_ROUTE(app, "/lcm/<string>/<string>")
    ([&](const std::string& aStr, const std::string& bStr) {
      long long a = std::stoll(aStr);
      long long b = std::stoll(bStr);
      long long result = MathUtils::LCM(a,b);
      return std::to_string(result);
    });
}
