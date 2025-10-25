# PH ATM Simulator - Docker Instructions

## Building the Docker Image

```bash
docker build -t atm-simulator .
```

## Running the ATM Simulator

### Option 1: Run without persistent data
```bash
docker run -it --rm atm-simulator
```

### Option 2: Run with persistent data (recommended)
This will save your balance and transactions between container runs:

```bash
# Create a named volume
docker volume create atm-data

# Run the container with the volume
docker run -it --rm -v atm-data:/app/data atm-simulator
```

### Option 3: Run with local directory mapping
This will store data in your current directory:

```bash
docker run -it --rm -v $(pwd)/data:/app/data atm-simulator
```

## Viewing Persistent Data

If using a named volume:
```bash
# List files in the volume
docker run --rm -v atm-data:/app/data alpine ls -la /app/data

# View balance
docker run --rm -v atm-data:/app/data alpine cat /app/data/balance.txt

# View transactions
docker run --rm -v atm-data:/app/data alpine cat /app/data/transactions.txt
```

If using local directory mapping:
```bash
# Just check your local data directory
ls -la data/
cat data/balance.txt
cat data/transactions.txt
```

## Cleaning Up

```bash
# Remove the Docker image
docker rmi atm-simulator

# Remove the volume (this will delete all data!)
docker volume rm atm-data
```
