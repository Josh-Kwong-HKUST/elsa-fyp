# Market Simulation for Algorithmic Trading

ELSA (Electronic Limit-order Simulation for Algorithmic trading) - A comprehensive platform for simulating market conditions and testing algorithmic trading strategies.

## Project Structure

- **`client/`** - C++ client application for trading simulation engine
- **`frontend/`** - React-based web interface for monitoring and visualization
- **`tests/`** - Unit and integration tests
- **`scripts/`** - Build and utility scripts

## Components

### C++ Client

The core trading simulation engine built with C++ 23.

**Building:**
```bash
cmake -B build
cmake --build build
./build/client/client
```

### Frontend

Web-based dashboard for real-time market data visualization and simulation monitoring.

**Getting Started:**
```bash
cd frontend
npm install
npm run dev
```

See [frontend/README.md](frontend/README.md) for more details.

## Testing

```bash
# Build tests
bash scripts/build_test.sh

# Run tests
cd build-test
ctest
```

## Requirements

- CMake 3.20+
- C++23 compatible compiler (GCC 13+, Clang 16+)
- Node.js 18+ (for frontend)
- Catch2 3+ (for tests)

## License

This project is part of a Final Year Project (FYP).
