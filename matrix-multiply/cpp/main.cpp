#include "main.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
  const size_t rows_a = 1000;
  const size_t cols_a = 500;

  const size_t rows_b = 500;
  const size_t cols_b = 1000;

  const int num_range = 100;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(1, num_range);

  vector<vector<int>> a(rows_a, vector<int>(cols_a, 0));
  vector<vector<int>> b(rows_a, vector<int>(cols_a, 0));

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[0].size(); j++) {
      a[i][j] = distrib(gen);
    }
  }

  for (int i = 0; i < b.size(); i++) {
    for (int j = 0; j < b[0].size(); j++) {
      b[i][j] = distrib(gen);
    }
  }

  auto start_sequential = chrono::high_resolution_clock::now();
  auto c = matrix_multiply(a, b);
  auto end_sequential = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_sequential =
      end_sequential - start_sequential;
  cout << "Time elapsed for sequential sorting: " << duration_sequential.count()
       << " seconds\n";

  return 0;
}