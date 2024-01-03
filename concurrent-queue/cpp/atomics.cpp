#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> ready(false);
int data = 0;

void producer() {
  data = 100;                                    // Write data
  ready.store(true, std::memory_order_relaxed);  // Set flag
}

void consumer() {
  while (!ready.load(std::memory_order_seq_cst))
    ;  // Wait for flag
  std::cout << "data: " << data << std::endl;
  if (data != 100) {  // Check data
    std::cerr << "data is not 100!" << std::endl;
    std::terminate();  // Fail if data is not as expected
  }
}

int main() {
  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join();
  t2.join();
  return 0;
}
