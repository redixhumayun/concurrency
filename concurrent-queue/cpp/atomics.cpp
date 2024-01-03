#include <atomic>
#include <iostream>
#include <thread>

// std::atomic<bool> ready(false);

void set_atomic_flag_values() {
  std::atomic_flag flag = ATOMIC_FLAG_INIT;
  bool x = flag.test_and_set();
  std::cout << x << std::endl;
  bool y = flag.test_and_set();
  std::cout << y << std::endl;
}

int main() { set_atomic_flag_values(); }

// int data = 0;

// void producer() {
//   data = 100;  // Write data
//   ready = true;
//   // ready.store(true);  // Set flag
// }

// void consumer() {
//   // while (!ready.load())
//   //   ;  // Wait for flag
//   while (!ready)
//     ;
//   std::cout << "data: " << data << std::endl;
//   if (data != 100) {  // Check data
//     std::cerr << "data is not 100!" << std::endl;
//     std::terminate();  // Fail if data is not as expected
//   }
// }

// int main() {
//   std::thread t1(producer);
//   std::thread t2(consumer);
//   t1.join();
//   t2.join();
//   return 0;
// }
