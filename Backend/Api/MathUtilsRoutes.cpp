#include <iostream>
#include <string>
#include <cstdint>
#include "MathUtilsRoutes.h"
#include "MathUtils.h"
#include <../CorsMiddleWare.h>

MathUtilsRoutes::MathUtilsRoutes(crow::App<CorsMiddleware> &app) {
    CROW_ROUTE(app, "/gcd/<string>/<string>")
    ([&](const std::string& aStr, const std::string& bStr) {
      long long a = std::stoll(aStr);
      long long b = std::stoll(bStr);
      long long result = MathUtils::GCD(a,b);

      crow::json::wvalue res;
      res["result"] = std::to_string(result);

      return res;
    });

    CROW_ROUTE(app, "/lcm/<string>/<string>")
    ([&](const std::string& aStr, const std::string& bStr) {
      long long a = std::stoll(aStr);
      long long b = std::stoll(bStr);
      long long result = MathUtils::LCM(a,b);

      crow::json::wvalue res;
        res["result"] = std::to_string(result);

      return res;
    });
}
