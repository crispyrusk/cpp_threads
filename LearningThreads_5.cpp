#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag;

void do_something() {
  std::call_once(flag, []() {std::cout << "called once" << std::endl; });
  std::cout << "called each time" << std::endl;
}

int main()  {
  std::thread t1(do_something);
  std::thread t2(do_something);
  std::thread t3(do_something);
  std::thread t4(do_something);
  std::thread t5(do_something);
  std::thread t6(do_something);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();

}