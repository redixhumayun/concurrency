#include "main.hpp"

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