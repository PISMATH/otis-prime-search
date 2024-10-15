# Otis Primes Finder

This repository contains tools for finding Otis primes, which are primes of the form \(2^k - 3\).

## Compilation

### Step 1: Compile `find_mods.c`
```bash
gcc find_mods.c -o find_mods
```

### Step 2: Install GMP
Ensure you have the GMP library installed on your system. You can install it using:

- **Ubuntu/Debian:**
  ```bash
  sudo apt-get install libgmp-dev
  ```
- **macOS (with Homebrew):**
  ```bash
  brew install gmp
  ```
- **Windows:**
  Download and install GMP from the official [GMP website](https://gmplib.org/).

### Step 3: Compile `find_primes.c`
```bash
gcc find_primes.c -o find_primes -lgmp
```

## Running the Program

### Step 1: Run `find_mods`
```bash
./find_mods 1000
```
You can change the number `1000` to adjust the optimization level.

### Step 2: Run `find_primes`
```bash
./find_primes 1000
```
You can change the number `1000` to find more Otis primes.

Note, the code is mostly black magic, I do not know how it works, but it does.
