cmake_minimum_required(VERSION 3.22)

project(MathRadical CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)

# Add Crow
CPMAddPackage(Crow
        VERSION 1.3.0
        GITHUB_REPOSITORY CrowCpp/Crow
        OPTIONS
        "CROW_BUILD_EXAMPLES Off"
        "CROW_BUILD_TOOLS Off"
        "CROW_BUILD_TESTS Off"
        "CROW_BUILD_DOCS Off"
        "CROW_ENABLE_COMPRESSION On"
)

# Add Catch2
CPMAddPackage(Catch2
        VERSION 3.7.0
        GITHUB_REPOSITORY catchorg/Catch2
        OPTIONS
        "CATCH_INSTALL_DOCS Off"
        "CATCH_INSTALL_EXTRAS Off"
        "CATCH_ENABLE_REPRODUCIBLE_BUILD Off"
)

# Core library
set(CORE_SOURCES
        Math/MathUtils.cpp
        Math/Fraction.cpp
)
add_library(MathRadicalCore STATIC ${CORE_SOURCES})
target_include_directories(MathRadicalCore PUBLIC ${CMAKE_SOURCE_DIR}/Math)

if(WIN32)
    set(PLATFORM_LIBS ws2_32 Mswsock)
endif()

# API library
add_library(MathRadicalApi
        Api/MathUtilsRoutes.cpp
        Api/MathUtilsRoutes.h
)
target_include_directories(MathRadicalApi PUBLIC ${CMAKE_SOURCE_DIR}/Api)
target_link_libraries(MathRadicalApi PUBLIC MathRadicalCore Crow::Crow ${PLATFORM_LIBS})

# Main executable
add_executable(MathRadical main.cpp)
target_link_libraries(MathRadical PRIVATE MathRadicalCore MathRadicalApi Crow::Crow ${PLATFORM_LIBS})

# Enable testing
include(CTest)
enable_testing()

# Fraction tests
add_executable(fraction_tests Test/Fraction_Test.cpp)
target_link_libraries(fraction_tests PRIVATE Catch2::Catch2WithMain MathRadicalCore MathRadicalApi)
add_test(NAME fraction_test_runner COMMAND fraction_tests)

# MathUtils tests
add_executable(math_utils_tests Test/Math_Utils_Test.cpp)
target_link_libraries(math_utils_tests PRIVATE Catch2::Catch2WithMain MathRadicalCore MathRadicalApi)
add_test(NAME math_utils_test_runner COMMAND math_utils_tests)
