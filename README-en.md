# PRNGAlgorithm - Pseudo-Random Number Generator using Linear Congruential Generator (LCG)

## 1. Introduction

This project implements a simple **Pseudo-Random Number Generator (PRNG)** algorithm based on the **Linear Congruential Generator (LCG)** method. The purpose is to illustrate the basic operation of a PRNG and compare it with modern libraries like `<random>` in C++.

Language used: `C++17`.

---

## 2. Theory: Pseudo-Random Number Generator (PRNG)

### What is a PRNG?

A PRNG is a **pseudo-random number generator**, which creates a sequence of numbers that appear random but are generated according to a deterministic algorithm. Each time it runs with the same initial value (seed), the PRNG will produce the same sequence of numbers.

> Note: PRNGs are **not suitable for encryption or security purposes** due to their deterministic nature.

### Linear Congruential Generator (LCG)

LCG is one of the simplest and most popular PRNG algorithms, with the formula:

```
Xₙ₊₁ = (a * Xₙ + c) mod m
```

Where:
- `Xₙ`: the number generated at step `n` (called the current state or seed),
- `a`: the multiplier,
- `c`: the increment,
- `m`: the modulus (value limit),
- `X₀`: the initial value (initial seed).

If the parameters `a`, `c`, and `m` are chosen appropriately, the generated sequence will have a long period and good distribution.

### Comparison with `<random>` in C++

C++ provides modern PRNGs in the `<random>` library, such as `std::mt19937` (Mersenne Twister), which offer much higher quality and performance compared to LCG:

```cpp
#include <random>

std::mt19937 gen(seed);
std::uniform_int_distribution<> dist(min, max);
int random_val = dist(gen);
```
---

## 3. Class Description: `SimplePRNG`

### Properties:

```cpp
unsigned long long current_seed;
unsigned long long multiplier;
unsigned long long increment;
unsigned long long modulus;
```

*   `current_seed`: the current state of the PRNG.
*   `multiplier` (`a`): the multiplier in the LCG formula.
*   `increment` (`c`): the increment added after each step.
*   `modulus` (`m`): the modulo value to keep the result within a limit.

### Constructor:

```cpp
SimplePRNG(unsigned long long initial_seed);
```

Initializes the object with `initial_seed`. Assigns fixed `a`, `c`, and `m` values that are calculated to ensure a long period (based on common values in LCG).

### Method `next()`:

```cpp
unsigned long long next();
```

Returns the next random number according to the LCG formula.

### Method `set_seed()`:

```cpp
void set_seed(unsigned long long new_seed);
```

Resets the seed to restart the random sequence from the same state.

### Method `get_random_range()`:

```cpp
int get_random_range(int min_val, int max_val);
```

Returns a random number within the range `[min_val, max_val]`. Handles value swapping if `min > max`.

---

## 4. Function `main()`: Testing and Demonstration

Contains test sections that demonstrate the features of `SimplePRNG`:

1.  **Generate a sequence of numbers from the same seed**:

    *   Illustrates the **deterministic** nature of the PRNG.
    *   Resetting the seed will generate the exact same initial sequence.

2.  **Compare two different seeds**:

    *   Different seed -> completely different result sequence.

3.  **Test generating numbers within a range**:

    *   Uses `get_random_range(min, max)` to generate integers within the range `[min, max]`.

4.  **Test with a dynamic seed (system time)**:

    *   Uses `std::chrono` to create a new seed each time the program runs.

---

## 5. Compilation and Execution

```bash
g++ -o simple_prng main.cpp
./simple_prng
```

---

## 6. Conclusion

This project provides a visual insight into the inner workings of a basic PRNG using C++. Although simple, this knowledge is fundamental to understanding how more complex PRNG libraries like `<random>` in C++ or solutions in cryptography work.

LCG should not be used for real-world applications that require high randomness or security.
