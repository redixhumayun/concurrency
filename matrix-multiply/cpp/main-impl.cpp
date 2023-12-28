#include <iostream>

#include "main.hpp"

using namespace std;

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
