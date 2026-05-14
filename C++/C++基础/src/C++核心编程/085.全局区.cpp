#include <iostream>
#include <string>
using namespace std;
// 全局变量
int global_a = 100;
int global_b = 200;
// const
const int global_const_a = 50;
const int global_const_b = 60;
int main()
{
  //  局部变量
  int local_a = 10;
  int local_b = 20;
  // 静态变量
  static int static_a = 30;
  static int static_b = 40;
  // 常量
  // 字符串常量
  string str = "hello world";
  // const 常量
  const int const_a = 50;
  const int const_b = 60;
  cout << "字符串常量的地址为：" << reinterpret_cast<uintptr_t>(&str) << endl;
  cout << "局部变量a的地址为：" << reinterpret_cast<uintptr_t>(&local_a) << endl;
  cout << "局部变量b的地址为：" << reinterpret_cast<uintptr_t>(&local_b) << endl;
  cout << "全局变量global_a的地址为：" << reinterpret_cast<uintptr_t>(&global_a) << endl;
  cout << "全局变量global_b的地址为：" << reinterpret_cast<uintptr_t>(&global_b) << endl;
  cout << "静态变量static_a的地址为：" << reinterpret_cast<uintptr_t>(&static_a) << endl;
  cout << "静态变量static_b的地址为：" << reinterpret_cast<uintptr_t>(&static_b) << endl;
  cout << "常量const_a的地址为：" << reinterpret_cast<uintptr_t>(&const_a) << endl;
  cout << "常量const_b的地址为：" << reinterpret_cast<uintptr_t>(&const_b) << endl;
  cout << "全局常量global_const_a的地址为：" << reinterpret_cast<uintptr_t>(&global_const_a) << endl;
  return 0;
}