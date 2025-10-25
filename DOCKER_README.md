# PH ATM Simulator - Docker Instructions

## Building the Docker Image

```bash
docker build -t atm-simulator .
```

## Running the ATM Simulator

**IMPORTANT**: This is an interactive terminal application. It **must be run from the command line** with the `-it` flags. It cannot be run properly from Docker Desktop's GUI.

### Recommended: Run with persistent data from command line

This will save your balance and transactions in a local `data` folder:

```bash
docker run -it --rm -v $(pwd)/data:/data atm-simulator
```

### Option 1: Run without persistent data
```bash
docker run -it --rm atm-simulator
```

### Option 2: Run with Docker named volume
```bash
# Create a named volume
docker volume create atm-data

# Run the container with the volume
docker run -it --rm -v atm-data:/data atm-simulator
```

## Why can't I run this from Docker Desktop GUI?

Docker Desktop's GUI doesn't properly support fully interactive terminal applications that require real-time user input. When you click "Run" in the GUI:
- The container starts but has no interactive terminal attached
- The program can't read user input
- The container exits immediately

**Solution**: Always use the command line with `-it` flags for interactive applications like this ATM simulator.

## Viewing Persistent Data

If using local directory mapping (recommended):
```bash
# Just check your local data directory
ls -la data/
cat data/balance.txt
cat data/transactions.txt
```

If using a named volume:
```bash
# List files in the volume
docker run --rm -v atm-data:/data alpine ls -la /data

# View balance
docker run --rm -v atm-data:/data alpine cat /data/balance.txt

# View transactions
docker run --rm -v atm-data:/data alpine cat /data/transactions.txt
```

## Cleaning Up

```bash
# Remove the Docker image
docker rmi atm-simulator

# Remove the volume (this will delete all data!)
docker volume rm atm-data
```
