cmake_minimum_required(VERSION 4.0)
project(MathRadical)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#testing framework

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         v3.6.0
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(Catch2)

set(CORE_SOURCES
        Math/MathUtils.cpp
        Math/Fraction.cpp
)

add_executable(MathRadical
        main.cpp
        ${CORE_SOURCES}
)
#fraction test
set(FRACTION_TEST_SOURCES
        Test/Fraction_Test.cpp
)

add_executable(fraction_tests ${FRACTION_TEST_SOURCES} ${CORE_SOURCES})

target_link_libraries(fraction_tests PRIVATE
        Catch2::Catch2WithMain
)

#mathutils test

set(MATH_UTILS_TEST_SOURCES
        Test/Math_Utils_Test.cpp
)

add_executable(math_utils_tests ${MATH_UTILS_TEST_SOURCES} ${CORE_SOURCES})


target_link_libraries(math_utils_tests PRIVATE
        Catch2::Catch2WithMain
)

#enable c test
include(CTest)
add_test(NAME fraction_test_runner COMMAND fraction_tests)
add_test(NAME math_utils_test_runner COMMAND math_utils_tests)