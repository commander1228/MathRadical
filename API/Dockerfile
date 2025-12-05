# --- Build Stage ---
FROM python:3.9-slim AS builder

WORKDIR /app

# Install build tools
RUN pip install grpcio-tools

COPY MathEngine.proto .
RUN mkdir -p gen
RUN python -m grpc_tools.protoc -I. --python_out=./gen --grpc_python_out=./gen MathEngine.proto

# --- Runtime Stage ---
FROM python:3.9-slim AS runtime

WORKDIR /app

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .
COPY --from=builder /app/gen ./gen

# Expose port 5000 for Flask
EXPOSE 5000

CMD ["python", "gateway.py"]
