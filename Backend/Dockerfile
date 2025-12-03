FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    libasio-dev \
    dos2unix \
    zlib1g-dev \
    python3 \
    ninja-build \
    ccache \
    && rm -rf /var/lib/apt/lists/*

# Configure ccache
ENV PATH="/usr/lib/ccache:$PATH"

# Set CPM Cache directory
ENV CPM_SOURCE_CACHE=/var/cache/cpm
RUN mkdir -p $CPM_SOURCE_CACHE

# Pre-warm CPM cache by running a dummy configuration
# We copy only the necessary files to trigger dependency downloads
WORKDIR /tmp/warmup
COPY CMakeLists.txt .
COPY cmake ./cmake
# Create a dummy main.cpp if it doesn't exist, or just copy the real one if it's small
COPY main.cpp .
# Create dummy source files referenced in CMakeLists.txt to satisfy add_library/add_executable
RUN mkdir -p Math Api Test && \
    touch Math/MathUtils.cpp Math/Fraction.cpp && \
    touch Api/MathUtilsRoutes.cpp Api/MathUtilsRoutes.h && \
    touch Test/Fraction_Test.cpp Test/Math_Utils_Test.cpp

# Run CMake to download dependencies
RUN cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

# Clean up warmup directory
WORKDIR /app
RUN rm -rf /tmp/warmup

CMD ["/bin/bash", "-c", "mkdir -p build && cd build && if [ -f CMakeCache.txt ] && grep -q 'Unix Makefiles' CMakeCache.txt; then echo 'Detected Unix Makefiles generator. Cleaning build directory for Ninja...' && rm -rf *; fi && cmake -G Ninja .. && ninja && ./MathRadical"]
