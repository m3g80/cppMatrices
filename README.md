
# C++ Matrix Library for Parallel Computing

## Overview
An efficient C++ library for matrix operations optimized with **OpenMP** for parallel computing. Designed for high-performance applications, it supports matrix multiplication, inversion, determinant calculation, and row reduction (RREF) with up to **300% faster computation times**.

## Features
- **Parallelized Operations**: Multi-threaded matrix calculations using **OpenMP**.
- **Core Functions**:
  - Matrix multiplication
  - Determinant calculation
  - RREF computation
  - Random matrix generation
- **Scalable and Efficient**: Optimized for small to large matrix sizes.

## Getting Started

### Prerequisites
- **C++11** or higher compiler with OpenMP support (e.g., GCC, Clang).
- Git (optional, for cloning the repo).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/m3g80/cppMatrices.git
   cd cppMatrices
   ```
2. Build the project:
   ```bash
   clang++ -std=c++11 -fopenmp -o matrixLib src/main.cpp
   ```
3. Run the executable:
   ```bash
   ./matrixLib
   ```
