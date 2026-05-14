#include <iostream>
using namespace std;
// 不要返回局部变量的引用
// int &test01()
// {
//     int a = 10; // 局部变量
//     return a;
// }
// 返回静态b变量引用
int &test02()
{
  static int b = 10;
  return b;
}
int main()
{
  // 不能返回局部变量的引用
  // int &ref = test01();
  // cout << "ref=" << ref << endl;
  // cout << "ref=" << ref << endl; //错误 第一次结果正确，是因为编译器做了保留
  //  如果函数做左值，那么必须返回引用
  int &ref2 = test02();
  cout << "ref2=" << ref2 << endl;
  cout << "ref2=" << ref2 << endl;
  test02() = 1000;
  cout << "ref2=" << ref2 << endl;
  cout << "ref2=" << ref2 << endl;
  return 0;
}