FROM node:20-slim

WORKDIR /app

# Copy package files first for better caching
COPY package.json package-lock.json ./

# Install dependencies
RUN npm install

# We don't copy the rest of the source here because we'll mount it
# This ensures node_modules is populated in the container

CMD ["npm", "run", "dev", "--", "--host"]
