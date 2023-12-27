#include <gtest/gtest.h>

#include <vector>

#include "main.hpp"

using namespace std;

TEST(SequentialMergeSortTest, SimpleTest) {
  vector<int> arr = {5, 4, 3, 2, 1};
  merge_sort(arr);
  vector<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr, expected);
}

TEST(ParallelMergeSortTest, SimpleTest) {
  vector<int> arr = {5, 4, 3, 2, 1};
  merge_sort_parallel(arr);
  vector<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr, expected);
}