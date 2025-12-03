#include <crow.h>
#include "Api/MathUtilsRoutes.h"

int main() {
    crow::SimpleApp app;

    MathUtilsRoutes mathUtilRoutes(app);

    app.port(18080).multithreaded().run();

}