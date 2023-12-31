#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <shared_mutex>

using namespace std;

template <typename T>
class Queue {
 private:
  queue<T> q;
  shared_mutex m;
  condition_variable_any cv;

 public:
  Queue() = default;
  ~Queue() = default;
  Queue(const Queue&) = delete;
  Queue& operator=(const Queue&) = delete;

  void print(queue<T> q) {
    while (!q.empty()) {
      T value = q.front();
      cout << "The value is: " << value << endl;
      q.pop();
    }
  }

  void push(T value) {
    unique_lock<shared_mutex> lock(m);
    q.push(value);
    cv.notify_one();
  }

  optional<T> pop() {
    unique_lock<shared_mutex> lock(m);
    cv.wait(lock, [this] { return !q.empty(); });
    T value = q.front();
    q.pop();
    return value;
  }

  T front() {
    shared_lock<shared_mutex> lock(m);
    return q.front();
  }

  T back() {
    shared_lock<shared_mutex> lock(m);
    return q.back();
  }

  bool empty() {
    shared_lock<shared_mutex> lock(m);
    return q.empty();
  }

  int size() {
    shared_lock<shared_mutex> lock(m);
    return q.size();
  }
};