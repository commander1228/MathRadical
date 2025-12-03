#include <crow.h>
#include "Api/MathUtilsRoutes.h"
#include "CorsMiddleWare.h"

int main() {

    crow::App<CorsMiddleware> app;

    app.loglevel(crow::LogLevel::Debug);

    MathUtilsRoutes mathUtilRoutes(app);

    app.port(18080).multithreaded().run();

}