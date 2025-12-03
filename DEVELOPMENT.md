# Developer Environment Setup

This project uses Docker to containerize both the C++ Backend and the Vue.js Frontend for a consistent local development environment.

## Prerequisites

- **Docker Desktop**: Ensure Docker is installed and running.
- **Git**: For version control.

## Quick Start

1.  **Clone the repository** (if you haven't already):
    ```bash
    git clone https://github.com/commander1228/MathRadical
    cd MathRadical
    ```

2.  **Start the Environment**:
    Run the following command in the project root:
    ```bash
    docker compose up --build
    ```

3.  **Access the Application**:
    - **Frontend**: [http://localhost:5173](http://localhost:5173)
    - **Backend API**: [http://localhost:8080](http://localhost:8080)

## Development Workflow

The source code is mounted into the containers, so changes you make locally are reflected inside.

### Frontend (`/Frontend`)
- **Hot Reload**: Enabled by default. Changes to `.vue`, `.ts`, or `.css` files will automatically update the browser.

### Backend (`/Backend`)
- **Rebuilding**: Since C++ is compiled, you must rebuild the backend after making changes.
- **Option 1 (Restart Container)**:
    ```bash
    docker compose restart backend
    ```
- **Option 2 (Build inside container)**:
    For faster feedback without restarting the container:
    ```bash
    docker compose exec backend /bin/bash -c "cd build && cmake .. && make && ./MathRadical"
    ```

## Stopping the Environment

To stop the containers and free up ports:
```bash
docker compose down
```
