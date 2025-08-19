#include <iostream>
#include <chrono>
#include <cmath>
#include <random>

volatile double sink;  // Global volatile to ensure side effects

int main() {
    const int iterations = 100'000'000;  // 100 million iterations
    double sum = 0.0;

    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Start timing in nanoseconds
    auto start = std::chrono::high_resolution_clock::now();

    // Computation-heavy loop
    for (int i = 0; i < iterations; ++i) {
        double x = dist(rng);
        sum += std::sqrt(std::sin(x) * std::sin(x) + std::cos(x) * std::cos(x));
    }

    sink = sum;  // Assign to volatile variable

    // End timing in nanoseconds
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Result: " << sum << " (should be ~" << iterations << ")\n";
    std::cout << "Elapsed time: " << elapsed.count() << " ns\n";

    return 0;
}

