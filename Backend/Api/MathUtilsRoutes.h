#pragma once
#ifndef MATHRADICAL_MATHUTILSROUTES_H
#define MATHRADICAL_MATHUTILSROUTES_H
#include <../CorsMiddleWare.h>
#include <crow.h>

class MathUtilsRoutes {
public:
    MathUtilsRoutes(crow::App<CorsMiddleware>& app);
};

#endif //MATHRADICAL_MATHUTILSROUTES_H