#include <gtest/gtest.h>

#include <vector>

#include "main.hpp"

using namespace std;

TEST(MatrixMultiplication, Sequential) {
  vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}};
  vector<vector<int>> b = {{7, 8}, {9, 10}, {11, 12}};
  auto output_matrix = matrix_multiply(a, b);
  vector<vector<int>> expected = {{58, 64}, {139, 154}};
  EXPECT_EQ(output_matrix, expected);
}

TEST(MatrixMultiplication, NoBuffer) {
  vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}};
  vector<vector<int>> b = {{7, 8}, {9, 10}, {11, 12}};
  auto output_matrix = matrix_multiply_no_buffer(a, b);
  vector<vector<int>> expected = {{58, 64}, {139, 154}};
  EXPECT_EQ(output_matrix, expected);
}

TEST(MatrixMultiplication, Tiles) {
  vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}};
  vector<vector<int>> b = {{7, 8}, {9, 10}, {11, 12}};
  auto output_matrix = matrix_multiply_with_tiles(a, b);
  vector<vector<int>> expected = {{58, 64}, {139, 154}};
  EXPECT_EQ(output_matrix, expected);
}