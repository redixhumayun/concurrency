#include "main.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
  // Constants
  const size_t VECTOR_SIZE = 10000000;  // Adjust size as needed
  const int NUMBER_RANGE = 100;         // Range of random numbers

  // Random number generation setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, NUMBER_RANGE);

  // Generate random numbers
  std::vector<int> numbers(VECTOR_SIZE);
  for (auto& num : numbers) {
    num = distrib(gen);
  }

  // Clone the vector for a fair comparison
  std::vector<int> numbers_for_sequential = numbers;

  // Time parallel sort
  auto start_concurrent = std::chrono::high_resolution_clock::now();
  merge_sort_parallel(numbers);
  auto end_concurrent = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration_concurrent =
      end_concurrent - start_concurrent;

  // Time sequential sort
  auto start_sequential = std::chrono::high_resolution_clock::now();
  merge_sort(numbers_for_sequential);
  auto end_sequential = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration_sequential =
      end_sequential - start_sequential;

  // Print results
  std::cout << "Time elapsed for concurrent sorting: "
            << duration_concurrent.count() << " seconds\n";
  std::cout << "Time elapsed for sequential sorting: "
            << duration_sequential.count() << " seconds\n";

  return 0;
}
