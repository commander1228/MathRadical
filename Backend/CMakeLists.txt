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

# --- gRPC Code Generation Function ---
function(generate_grpc_cpp PROTO_FILE OUTPUT_DIR)
    # Ensure the output directory exists
    file(MAKE_DIRECTORY ${OUTPUT_DIR})

    # Base name of proto file
    get_filename_component(BASE_NAME ${PROTO_FILE} NAME_WE)

    # Generated file paths
    set(PROTO_C "${OUTPUT_DIR}/${BASE_NAME}.pb.cc")
    set(GRPC_C  "${OUTPUT_DIR}/${BASE_NAME}.grpc.pb.cc")
    set(PROTO_H "${OUTPUT_DIR}/${BASE_NAME}.pb.h")
    set(GRPC_H  "${OUTPUT_DIR}/${BASE_NAME}.grpc.pb.h")

    # gRPC plugin
    get_target_property(GRPC_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin LOCATION)
    if(NOT GRPC_PLUGIN_EXECUTABLE)
        message(FATAL_ERROR "Could not find gRPC plugin executable. Please ensure vcpkg installed grpc[codegen].")
    endif()

    # Generate protobuf and gRPC code
    execute_process(
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
            --proto_path ${CMAKE_CURRENT_SOURCE_DIR}
            --cpp_out ${OUTPUT_DIR}
            --grpc_out ${OUTPUT_DIR}
            --plugin=protoc-gen-grpc=${GRPC_PLUGIN_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_FILE}  # absolute path
            RESULT_VARIABLE GENERATE_RESULT
    )

    if(GENERATE_RESULT)
        message(FATAL_ERROR "gRPC code generation failed for ${PROTO_FILE}")
    endif()

    # Return generated files
    set(GENERATED_PROTO_SOURCES ${PROTO_C} ${GRPC_C} PARENT_SCOPE)
    set(GENERATED_PROTO_HEADERS ${PROTO_H} ${GRPC_H} PARENT_SCOPE)
endfunction()

# --- gRPC Server Setup ---
# Generate gRPC files into project root /generated_grpc
set(GRPC_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/generated_grpc")
file(MAKE_DIRECTORY ${GRPC_OUTPUT_DIR})  # ensure folder exists
set(SERVICE_PROTO "MathEngine.proto")

# Find existing math implementation files and server file
set(SERVER_SOURCES MathEngineServer.cpp)
file(GLOB MATH_IMPL_SOURCES "Math/*.cpp")

# Generate gRPC files
generate_grpc_cpp(${SERVICE_PROTO} ${GRPC_OUTPUT_DIR})

# Define gRPC Server executable
add_executable(MathEngineServer
        ${SERVER_SOURCES}
        ${MATH_IMPL_SOURCES}
        ${GENERATED_PROTO_SOURCES}
)

# Link libraries
target_link_libraries(MathEngineServer
        PRIVATE
        MathRadicalCore
        gRPC::grpc++
        gRPC::gpr
)

# Include directories
target_include_directories(MathEngineServer
        PUBLIC
        ${CMAKE_SOURCE_DIR}/Math
        ${GRPC_OUTPUT_DIR}  # headers are here
)

# --- Testing ---
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
