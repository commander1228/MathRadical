# --- Build Stage ---
FROM ubuntu:22.04 AS builder

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
    protobuf-compiler \
    libprotobuf-dev \
    libgrpc++-dev \
    libgrpc-dev \
    protobuf-compiler-grpc \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure ccache
ENV PATH="/usr/lib/ccache:$PATH"

# Set CPM Cache directory
ENV CPM_SOURCE_CACHE=/var/cache/cpm
RUN mkdir -p $CPM_SOURCE_CACHE

# Pre-warm CPM cache
WORKDIR /tmp/warmup
COPY CMakeLists.txt .
COPY cmake ./cmake
COPY MathEngineServer.cpp .
COPY MathEngine.proto .
RUN mkdir -p Math Api Test && \
    touch Math/MathUtils.cpp Math/Fraction.cpp Math/MathEngineValidator.cpp && \
    touch Test/Fraction_Test.cpp Test/Math_Utils_Test.cpp

# Run CMake to download dependencies
RUN cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

# Copy source code and build
WORKDIR /app
COPY . .
RUN cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --target MathEngineServer

# --- Runtime Stage ---
FROM ubuntu:22.04 AS runtime

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libasio-dev \
    zlib1g \
    libprotobuf-dev \
    libgrpc++-dev \
    libgrpc-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy executable from builder
COPY --from=builder /app/build/MathEngineServer .

# Expose the gRPC port
EXPOSE 50051

# Run the server
CMD ["./MathEngineServer"]
