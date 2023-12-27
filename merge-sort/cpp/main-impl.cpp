#include <thread>
#include <vector>

#include "main.hpp"
using namespace std;

const int THRESHOLD = 10000;

void merge(vector<int>& left, vector<int>& right, vector<int>& ret) {
  int left_index = 0;
  int right_index = 0;
  int ret_index = 0;

  while (left_index < left.size() && right_index < right.size()) {
    if (left[left_index] <= right[right_index]) {
      ret[ret_index] = left[left_index];
      left_index++;
    } else {
      ret[ret_index] = right[right_index];
      right_index++;
    }
    ret_index++;
  }

  while (left_index < left.size()) {
    ret[ret_index] = left[left_index];
    left_index++;
    ret_index++;
  }

  while (right_index < right.size()) {
    ret[ret_index] = right[right_index];
    right_index++;
    ret_index++;
  }
}

void merge_sort_parallel(vector<int>& arr) {
  int mid = arr.size() / 2;
  if (mid == 0) {
    return;
  }

  if (arr.size() < THRESHOLD) {
    merge_sort(arr);
    return;
  }

  vector<int> left(arr.begin(), arr.begin() + mid);
  vector<int> right(arr.begin() + mid, arr.end());

  std::thread left_thread([&left]() { merge_sort_parallel(left); });
  merge_sort_parallel(right);
  left_thread.join();

  vector<int> ret(arr.size());

  merge(left, right, ret);
  arr = std::move(ret);
}

void merge_sort(std::vector<int>& arr) {
  int mid = arr.size() / 2;
  if (mid == 0) {
    return;
    ;
  }

  vector<int> left(arr.begin(), arr.begin() + mid);
  vector<int> right(arr.begin() + mid, arr.end());

  merge_sort(left);
  merge_sort(right);

  vector<int> ret(arr.size());

  merge(left, right, ret);

  arr = std::move(ret);
}