#include "main.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
  const size_t rows_a = 1000;
  const size_t cols_a = 1000;

  const size_t rows_b = 1000;
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

  auto start_no_buffer = chrono::high_resolution_clock::now();
  auto d = matrix_multiply_no_buffer(a, b);
  auto end_no_buffer = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_no_buffer = end_no_buffer - start_no_buffer;
  cout << "Time elapsed for no buffer sorting: " << duration_no_buffer.count()
       << " seconds\n";

  auto b_transponse = matrix_transpose(b);
  auto start_transpose = chrono::high_resolution_clock::now();
  auto e = matrix_multiply(a, b_transponse);
  auto end_transpose = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_transpose = end_transpose - start_transpose;
  cout << "Time elapsed for transpose sorting: " << duration_transpose.count()
       << " seconds\n";

  auto start_parallel = chrono::high_resolution_clock::now();
  auto f = matrix_multiply_parallel(a, b);
  auto end_parallel = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_parallel = end_parallel - start_parallel;
  cout << "Time elapsed for parallel sorting: " << duration_parallel.count()
       << " seconds\n";

  return 0;
}