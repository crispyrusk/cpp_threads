#include <thread>
#include <iostream>
#include <vector>
#include <mutex>


struct Counter {
  int value;

  Counter() : value(0) {}

  void increment() {
    ++value;
  }

  void decrement() {
    if (value == 0) { throw "value cannot be less than zero."; }
    --value;
  }

  int val() {
    return value;
  }

};


struct ConcurrentCounter {
  std::mutex mutex;
  Counter counter;

  void increment() {
    std::lock_guard<std::mutex> guard(mutex);
    counter.increment();
  }

  void decrement() {
    std::lock_guard<std::mutex> guard(mutex);
    counter.decrement();
  }

  int val() {
    return counter.value;
  }
};


template<typename T>
void testCounter()  {
  T counter;

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread([&counter](){
      for (int j = 0; j < 100; ++j) {
        counter.increment();
      }
    }));
    threads.push_back(std::thread([&counter](){
      for (int j = 0; j < 10; ++j) {
        counter.decrement();
      }
    }));
  }


  for (auto& thread : threads) {
    thread.join();
  }

  std::cout << counter.val() << std::endl;
}

int main() {
  
  for (int i = 0; i < 10; ++i) {
    testCounter<Counter>();
  }

  for (int i = 0; i < 10; ++i) {
    testCounter<ConcurrentCounter>();
  }


  return 0;
}