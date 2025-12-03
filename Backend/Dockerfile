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
    && rm -rf /var/lib/apt/lists/*

# Install Crow
# Crow is a header-only library, but we need to install its cmake config files
WORKDIR /tmp
RUN git clone https://github.com/CrowCpp/Crow.git && \
    cd Crow && \
    mkdir build && cd build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    make install

WORKDIR /app

# We don't copy source here because we'll mount it in docker-compose for dev
# But we can set up a build directory
RUN mkdir -p build

# Simple entrypoint script to build and run
# In a real dev env, you might want something that watches for changes
COPY <<EOF /entrypoint.sh
#!/bin/bash
set -e
cd build
cmake ..
make -j\$(nproc)
./MathRadical
EOF

RUN chmod +x /entrypoint.sh

CMD ["/entrypoint.sh"]
