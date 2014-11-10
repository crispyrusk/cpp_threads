 // atomic

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

struct AtomicCounter {
  std::atomic<int> value;

  void increment(){
    ++value;
  }

  void decrement(){
    --value;
  }

  int get(){
    return value.load();
  }
};


int main() {
  std::vector<std::thread> threads;
  AtomicCounter counter;
  for (int i = 0; i < 100; ++i) {
    threads.push_back(std::thread([&counter](){
      counter.increment();
    }));
  }

  for (auto& x : threads) {
    x.join();
  }

  std::cout << counter.get() << std::endl;
  return 0;

}