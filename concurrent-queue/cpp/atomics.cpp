#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>

int data = 0;
std::atomic<bool> ready(false);

void producer() {
  data = 100;
  ready.store(true, std::memory_order_relaxed);  // Set flag
}

void consumer() {
  while (!ready.load(std::memory_order_relaxed))
    ;
  assert(data == 100);
}

int main() {
  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join();
  t2.join();
  return 0;
}
