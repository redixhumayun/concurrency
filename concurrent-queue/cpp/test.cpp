#include <gtest/gtest.h>

#include <thread>

#include "main.hpp"

using namespace std;

TEST(QueueTest, BasicOperations) {
  Queue<int> q;
  ASSERT_TRUE(q.empty());

  q.push(1);
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(q.front(), 1);
  ASSERT_EQ(q.back(), 1);

  q.push(2);
  ASSERT_EQ(q.back(), 2);

  auto val = q.pop();
  ASSERT_TRUE(val.has_value());
  ASSERT_EQ(val.value(), 1);
  ASSERT_EQ(q.front(), 2);

  val = q.pop();
  ASSERT_TRUE(val.has_value());
  ASSERT_EQ(val.value(), 2);
  ASSERT_TRUE(q.empty());
}

void producer(Queue<int>& q, int start, int end) {
  for (int i = 0; i < end; i++) {
    q.push(i);
  }
}

void consumer(Queue<int>& q, int count, vector<int>& results) {
  for (int i = 0; i < count; i++) {
    auto value = q.pop();
    if (value.has_value()) {
      results.push_back(value.value());
    }
  }
  cout << "Results size: " << results.size() << endl;
}

TEST(QueueTest, ThreadSafety) {
  Queue<int> q;
  vector<int> results;
  const int num_elements = 1000;

  thread t1(producer, std::ref(q), 0, num_elements);
  thread t2(consumer, std::ref(q), num_elements, std::ref(results));

  t1.join();
  t2.join();

  ASSERT_EQ(results.size(), num_elements);
}