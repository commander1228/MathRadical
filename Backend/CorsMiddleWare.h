//
// Created by kianw on 12/2/2025.
//

#ifndef MATHRADICAL_CORSMIDDLEWARE_H
#define MATHRADICAL_CORSMIDDLEWARE_H

#include <crow.h>

struct CorsMiddleware {
    struct context {};

    void before_handle(crow::request& /*req*/, crow::response& /*res*/, context& /*ctx*/) {
    }

    void after_handle(crow::request& /*req*/, crow::response& res, context& /*ctx*/) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }
};

#endif //MATHRADICAL_CORSMIDDLEWARE_H