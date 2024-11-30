// 参考自 https://www.cnblogs.com/qicosmos/archive/2013/04/28/3048919.html
// MessageBus的测试程序
// g++ .\TestMessageBus.cpp -std=c++17 -o TestMessageBus

#include <iostream>

#include "../MessageBus.hpp"
using namespace std;

struct A {
  void Test(int x) { cout << x << endl; }
  void GTest() { cout << "it is a test" << endl; }
  void HTest(int x) const { cout << "it is a HTest" << endl; }
  void InnerAttach() { MessageBus::Attach("aa", &A::Test, this); }
};

void GG(int x) { cout << "it is a gg" << endl; }

void GG1() { cout << "it is a GG" << endl; }

void TestMessageBus() {
  A a;
  a.InnerAttach();
  MessageBus::Notify("aa", 3);
  std::cout << "hello\n";
  MessageBus bus;
  MessageBus::Attach("aa", &A::Test, &a);
  int x = 3;
  MessageBus::Notify("aa", 3);

  MessageBus::Attach("hh", &A::HTest, &a);
  MessageBus::Notify("hh", x);
  MessageBus::Attach("bb", &A::GTest, &a);
  MessageBus::Notify("bb");

  MessageBus::Attach<int>("gg", GG);
  MessageBus::Notify("gg", 3);

  MessageBus::Attach("gg", GG1);
  MessageBus::Notify("gg");
  std::cout << "bye\n";
}

int main() {
  TestMessageBus();
  return 0;
}