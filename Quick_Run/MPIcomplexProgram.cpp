#include <iostream>
#include <chrono>
#include <cmath>
#include <random>
#include <mpi.h>

volatile double sink; // Global volatile to ensure side effects

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long total_iterations = 100'000'000LL; // 100 million iterations

    // Split work across processes
    long long chunk = total_iterations / size;
    long long start = rank * chunk;
    long long end = (rank == size - 1) ? total_iterations : start + chunk;

    double sum = 0.0;
    std::mt19937_64 rng(std::random_device{}() + rank); // Different seed per process
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Synchronize before timing
    MPI_Barrier(MPI_COMM_WORLD);
    auto start_t = std::chrono::high_resolution_clock::now();

    // Computation-heavy loop
    for (long long i = start; i < end; ++i) {
        double x = dist(rng);
        sum += std::sqrt(std::sin(x) * std::sin(x) + std::cos(x) * std::cos(x));
    }
    sink = sum; // Assign to volatile variable

    // Synchronize before final timing
    MPI_Barrier(MPI_COMM_WORLD);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);

    // Reduce sum to root process
    double global_sum = 0.0;
    MPI_Reduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Global sum: " << global_sum << " (should be ~" << total_iterations << ")\n";
        std::cout << "Elapsed time: " << elapsed.count() << " ns\n";
        std::cout << "Number of processes: " << size << "\n";
    }

    MPI_Finalize();
    return 0;
}

