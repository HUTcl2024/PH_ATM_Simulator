# Use Alpine Linux with GCC for a minimal image
FROM alpine:latest

# Install build essentials
RUN apk add --no-cache gcc musl-dev

# Set working directory
WORKDIR /usr/local/bin

# Copy the source code
COPY PH_ATM_Simulator/main.c .

# Compile the program
RUN gcc -std=c11 -O2 main.c -o atm_simulator

# Set working directory to /data where files will be stored
WORKDIR /data

# Create a volume for persistent data storage
VOLUME /data

# Run the ATM simulator with interactive terminal
ENTRYPOINT ["/usr/local/bin/atm_simulator"]
