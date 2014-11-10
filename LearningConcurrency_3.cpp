// recursive lock
// recurrent mutex

#include <thread>
#include <mutex>
#include <iostream>

template<typename T>
struct Complex {
  T mutex;
  int i;

  Complex() : i(100) {}

  void mul(int x) {
    std::lock_guard<T> lock(mutex);
    i *= x;
  }

  void div(int x) {
    std::lock_guard<T> lock(mutex);
    i /= x;
  }

  void both(int x, int y) {
    std::lock_guard<T> lock(mutex);
    mul(x);
    div(y);
  }
};

int main() {
  //Complex<std::mutex> c;
  //c.both(3, 4); // deadlock
  Complex<std::recursive_mutex> c; // the same thread can relock the previously locked mutex
  c.both(3, 4); // deadlock
 
  return 0;
}

