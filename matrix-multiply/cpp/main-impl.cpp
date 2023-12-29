#include <iostream>
#include <thread>

#include "main.hpp"

using namespace std;

const int TILE_SIZE = 64;

vector<vector<int>> matrix_multiply(vector<vector<int>>& a,
                                    vector<vector<int>>& b) {
  int m = a.size();
  int n = a[0].size();
  int p = b[0].size();

  vector<vector<int>> c(
      m, vector<int>(p, 0));  //  m*p is the size of the output matrix

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      for (int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

vector<vector<int>> matrix_multiply_no_buffer(vector<vector<int>>& a,
                                              vector<vector<int>>& b) {
  int m = a.size();
  int n = a[0].size();
  int p = b[0].size();

  vector<vector<int>> c(m);  //  m*p is the size of the output matrix

  for (int i = 0; i < m; i++) {
    vector<int> c_row(p);
    for (int j = 0; j < p; j++) {
      int sum = 0;
      for (int k = 0; k < n; k++) {
        sum += a[i][k] * b[k][j];
      }
      c_row[j] = sum;
    }
    c[i] = c_row;
  }
  return c;
}

auto matrix_transpose(vector<vector<int>>& a) -> vector<vector<int>> {
  int m = a.size();
  int n = a[0].size();

  vector<vector<int>> a_transpose(n, vector<int>(m, 0));

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      a_transpose[j][i] = a[i][j];
    }
  }
  return a_transpose;
}

auto matrix_multiply_with_transpose(vector<vector<int>>& a,
                                    vector<vector<int>>& b)
    -> vector<vector<int>> {
  int m = a.size();
  int n = a[0].size();
  int p = b[0].size();

  vector<vector<int>> c(m);

  for (int i = 0; i < m; i++) {
    vector<int> c_row(p);
    for (int j = 0; j < p; j++) {
      int sum = 0;
      for (int k = 0; k < n; k++) {
        sum += a[i][k] * b[k][j];
      }
      c_row[j] = sum;
    }
    c[i] = c_row;
  }
  return c;
}

auto matrix_multiply_parallel(vector<vector<int>>& a, vector<vector<int>>& b)
    -> vector<vector<int>> {
  int m = a.size();
  int n = a[0].size();
  int p = b[0].size();

  vector<vector<int>> c(m);

#pragma omp parallel for
  for (int i = 0; i < m; i++) {
    vector<int> c_row(p);
    for (int j = 0; j < p; j++) {
      int sum = 0;
      for (int k = 0; k < n; k++) {
        sum += a[i][k] * b[k][j];
      }
      c_row[j] = sum;
    }
    c[i] = c_row;
  }
  return c;
}

auto matrix_multiply_tiles(const vector<vector<int>>& a,
                           const vector<vector<int>>& b, vector<vector<int>>& c,
                           int m, int n, int p, int i_start, int j_start)
    -> void {
  for (int i = 0; i < TILE_SIZE; i++) {
    for (int j = 0; j < TILE_SIZE; j++) {
      if (i_start + i < m && j_start + j < p) {
        for (int k = 0; k < n; k++) {
          c[i_start + i][j_start + j] += a[i_start + i][k] * b[k][j_start + j];
        }
      }
    }
  }
}

vector<vector<int>> matrix_multiply_with_tiles(vector<vector<int>>& a,
                                               vector<vector<int>>& b) {
  int m = a.size();
  int n = a[0].size();
  int p = b[0].size();

  vector<vector<int>> c(m, vector<int>(p, 0));

  vector<thread> threads;

  for (int i = 0; i < m; i += TILE_SIZE) {
    for (int j = 0; j < n; j += TILE_SIZE) {
      threads.emplace_back(matrix_multiply_tiles, std::cref(a), std::cref(b),
                           std::ref(c), m, n, p, i, j);
    }
  }

  for (auto& t : threads) {
    t.join();
  }
  return c;
}