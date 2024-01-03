#include <gtest/gtest.h>

#include "lock-free-queue.hpp"

TEST(LockFreeQueueTest, SingleThreadedEnqueueDequeue) {
  lock_free_queue<int> queue;

  // Enqueue elements
  queue.enqueue(1);
  queue.enqueue(2);

  // Dequeue elements
  auto first = queue.dequeue();
  auto second = queue.dequeue();

  EXPECT_EQ(*first, 1);
  EXPECT_EQ(*second, 2);
}