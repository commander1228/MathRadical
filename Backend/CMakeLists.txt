cmake_minimum_required(VERSION 3.22)
project(MathRadical CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CORE_SOURCES
        Math/MathUtils.cpp
        Math/Fraction.cpp
)

add_library(MathRadicalCore STATIC ${CORE_SOURCES})


add_executable(MathRadical main.cpp)

target_link_libraries(MathRadical PRIVATE MathRadicalCore)


include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         v3.6.0
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
include(CTest)

find_package(Crow CONFIG REQUIRED)
add_executable(my_project main.cpp)
target_link_libraries(my_project PRIVATE Crow::Crow)

#  Fraction Tests
# -----------------------------
set(FRACTION_TEST_SOURCES Test/Fraction_Test.cpp)
add_executable(fraction_tests ${FRACTION_TEST_SOURCES})

target_link_libraries(fraction_tests PRIVATE
        Catch2::Catch2WithMain
        MathRadicalCore
)
add_test(NAME fraction_test_runner COMMAND fraction_tests)

#  MathUtils Tests
# -----------------------------
set(MATH_UTILS_TEST_SOURCES Test/Math_Utils_Test.cpp)
add_executable(math_utils_tests ${MATH_UTILS_TEST_SOURCES})

target_link_libraries(math_utils_tests PRIVATE
        Catch2::Catch2WithMain
        MathRadicalCore
)
add_test(NAME math_utils_test_runner COMMAND math_utils_tests)