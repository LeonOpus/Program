#include <iostream>
using namespace std;
int *func() {
  // 指针本质也是局部变量，放在栈上，指针保存的数据是放在堆区
  int *p = new int(10);  // 利用new关键字，可以将数据开辟到堆区
  // int *p = new int(20);
  return p;
}
int main() {
  int *p = func();
  cout << *p << endl;
  cout << *p << endl;
  return 0;
}