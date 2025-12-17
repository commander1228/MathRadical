# Build Stage
FROM rust:1.83-slim-bookworm as builder

WORKDIR /usr/src/app

# Install protobuf compiler
RUN apt-get update && apt-get install -y protobuf-compiler && rm -rf /var/lib/apt/lists/*

# Create a dummy project to cache dependencies
RUN cargo init --bin

# Copy manifests
COPY Cargo.toml ./

# Build dependencies only (this layer will be cached unless Cargo.toml changes)
RUN cargo build --release
RUN rm -f target/release/deps/gateway_rust*

# Now copy the real source code
COPY . .

# Build the actual application
RUN cargo build --release

# Runtime Stage
FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /usr/src/app/target/release/gateway-rust /app/gateway-rust

# Expose the API port
EXPOSE 5000

ENV APP_ENV=production

CMD ["./gateway-rust"]
