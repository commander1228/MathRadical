set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
cmake_minimum_required(VERSION 3.20...3.30)



project(MathRadical CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)

# Add Catch2
CPMAddPackage(Catch2
        VERSION 3.7.0
        GITHUB_REPOSITORY catchorg/Catch2
        OPTIONS
        "CATCH_INSTALL_DOCS Off"
        "CATCH_INSTALL_EXTRAS Off"
        "CATCH_ENABLE_REPRODUCIBLE_BUILD Off"
)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)



# Core library
set(CORE_SOURCES
        Math/MathUtils.cpp
        Math/Fraction.cpp
        Math/MathEngineValidator.cpp
)
add_library(MathRadicalCore STATIC ${CORE_SOURCES})
target_include_directories(MathRadicalCore PUBLIC ${CMAKE_SOURCE_DIR}/Math)


function(generate_grpc_cpp PROTO_FILE)
    # Define paths for generated files
    string(REPLACE ".proto" "" BASE_NAME ${PROTO_FILE})

    set(PROTO_C "${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME}.pb.cc")
    set(GRPC_C "${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME}.grpc.pb.cc")

    # CRITICAL FIX: Get the absolute path to the gRPC plugin executable.
    get_target_property(GRPC_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin LOCATION)

    if(NOT GRPC_PLUGIN_EXECUTABLE)
        message(FATAL_ERROR "Could not find gRPC plugin executable. Please ensure vcpkg installed grpc[codegen].")
    endif()

    # Generate ALL files (.pb.cc, .pb.h, .grpc.pb.cc, .grpc.pb.h) in ONE command.
    execute_process(
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
            --proto_path ${CMAKE_CURRENT_SOURCE_DIR}
            --cpp_out ${CMAKE_CURRENT_BINARY_DIR}  # Standard Protobuf files
            --grpc_out ${CMAKE_CURRENT_BINARY_DIR} # gRPC Service files
            --plugin=protoc-gen-grpc=${GRPC_PLUGIN_EXECUTABLE} # Use the absolute path!
            ${PROTO_FILE}
            RESULT_VARIABLE GENERATE_RESULT
    )

    if (GENERATE_RESULT)
        message(FATAL_ERROR "gRPC code generation failed for ${PROTO_FILE}")
    endif()

    # Define variables to hold the generated files for linking
    set(GENERATED_PROTO_SOURCES
            ${PROTO_C}
            ${GRPC_C}
            PARENT_SCOPE)

    # Headers are auto-found by compiler path, but we keep the logic clean.
    set(GENERATED_PROTO_HEADERS
            "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_FILE}.pb.h"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_FILE}.grpc.pb.h"
            PARENT_SCOPE)
endfunction()


# --- gRPC Server Setup ---

# Define the service contract file
set(SERVICE_PROTO "MathEngine.proto")

# Find existing math implementation files and the new server file
set(SERVER_SOURCES
        MathEngineServer.cpp
        main.cpp
)
file(GLOB MATH_IMPL_SOURCES "Math/*.cpp")

# Run the Protobuf/gRPC Code Generation
generate_grpc_cpp(${SERVICE_PROTO})

# Define the gRPC Server Executable
add_executable(MathEngineServer
        ${SERVER_SOURCES}
        ${MATH_IMPL_SOURCES}
        ${GENERATED_PROTO_SOURCES}
)

# Link Libraries for the gRPC Server
target_link_libraries(MathEngineServer
        PRIVATE
        MathRadicalCore
        gRPC::grpc++
        protobuf
        gRPC::gpr
)

# Set Include Directories
target_include_directories(MathEngineServer
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Math # Your core headers
        ${CMAKE_CURRENT_BINARY_DIR} # To find generated headers (.pb.h, .grpc.pb.h)
)

# --- Testing ---

# Enable testing
include(CTest)
enable_testing()

# Fraction tests
add_executable(fraction_tests Test/Fraction_Test.cpp)
target_link_libraries(fraction_tests PRIVATE Catch2::Catch2WithMain MathRadicalCore)
add_test(NAME fraction_test_runner COMMAND fraction_tests)

# MathUtils tests
add_executable(math_utils_tests Test/Math_Utils_Test.cpp)
target_link_libraries(math_utils_tests PRIVATE Catch2::Catch2WithMain MathRadicalCore)
add_test(NAME math_utils_test_runner COMMAND math_utils_tests)