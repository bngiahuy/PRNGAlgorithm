#include <iostream>
#include <chrono>

class SimplePRNG {
private:
    unsigned long long current_seed; // Current state of the PRNG (Xn)
    unsigned long long multiplier;   // Multiplier (a)
    unsigned long long increment;    // Increment (c)
    unsigned long long modulus;      // Modulus (m)

public:
    // Constructor to initialize the PRNG with an initial seed
    SimplePRNG(unsigned long long initial_seed) {
        // Carefully chosen constants for good period and distribution
        multiplier = 1103515245ULL;  // Good 'a' value
        increment = 12345ULL;        // Good 'c' value
        modulus = 2147483648ULL;     // 2^31, good 'm' value (for 32-bit unsigned int)

        // Set initial seed
        current_seed = initial_seed;
    }

    // Method to generate the next random number
    unsigned long long next() {
        // Apply the LCG formula
        current_seed = (multiplier * current_seed + increment) % modulus;
        return current_seed;
    }

    // Method to reset the seed
    void set_seed(unsigned long long new_seed) {
        current_seed = new_seed;
    }

    // Method to get a random number in range [min, max]
    int get_random_range(int min_val, int max_val) {
        if (min_val > max_val) {
            int temp = min_val;
            min_val = max_val;
            max_val = temp;
        }

        long long range_val = static_cast<long long>(max_val) - min_val + 1;
        if (range_val == 0) return min_val;

        return min_val + (static_cast<int>(next() % range_val));
    }
};

int main() {
    std::cout << "--- Test with fixed seed ---" << std::endl;
    SimplePRNG prng1(12345);

    std::cout << "First 5 random numbers (Seed 12345):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << prng1.next() << " ";
    }
    std::cout << std::endl;

    std::cout << "Next 5 random numbers (Seed 12345):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << prng1.next() << " ";
    }
    std::cout << std::endl;

    prng1.set_seed(12345);
    std::cout << "5 random numbers after resetting seed (Seed 12345):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << prng1.next() << " ";
    }
    std::cout << std::endl;

    std::cout << "\n--- Test with different seed ---" << std::endl;
    SimplePRNG prng2(67890);
    std::cout << "First 5 random numbers (Seed 67890):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << prng2.next() << " ";
    }
    std::cout << std::endl;

    std::cout << "\n--- Test random range ---" << std::endl;
    SimplePRNG prng3(999);
    std::cout << "10 random numbers in range [1, 100] (Seed 999):" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << prng3.get_random_range(1, 100) << " ";
    }
    std::cout << std::endl;

    unsigned long long dynamic_seed = static_cast<unsigned long long>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );

    SimplePRNG dynamic_prng(dynamic_seed);

    std::cout << "--- Test with dynamic seed (changes every run) ---" << std::endl;
    std::cout << "Used seed: " << dynamic_seed << std::endl;
    std::cout << "10 random numbers:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << dynamic_prng.get_random_range(1, 100) << " ";
    }
    std::cout << std::endl;

    return 0;
}
