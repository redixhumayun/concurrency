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
  for (int i = start; i < end; i++) {
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

TEST(QueueTest, StressTestPush) {
  Queue<int> q;
  const int num_threads =
      10;  //  picking 10 because ARM processors have a 1:1 thread to core ratio
           //  and the M1 pro has 10 cores
  const int num_elements_per_thread = 100;

  vector<thread> threads;
  for (int i = 0; i < num_threads; i++) {
    threads.emplace_back(producer, std::ref(q), i * num_elements_per_thread,
                         (i + 1) * num_elements_per_thread);
  }

  for (auto& t : threads) {
    t.join();
  }

  ASSERT_EQ(q.size(), num_threads * num_elements_per_thread);
}

TEST(QueueTest, StressTestPushAndPop) {
  Queue<int> q;
  const int num_threads = 10;
  const int num_elements_per_thread = 100;

  vector<thread> threads;
  for (int i = 0; i < num_threads; i++) {
    threads.emplace_back(producer, std::ref(q), i * num_elements_per_thread,
                         (i + 1) * num_elements_per_thread);
  }

  vector<int> popped_values;
  threads.emplace_back(consumer, std::ref(q),
                       num_threads * num_elements_per_thread,
                       std::ref(popped_values));

  for (auto& t : threads) {
    t.join();
  }

  ASSERT_EQ(q.size(), 0);
}