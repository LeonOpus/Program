#include <iostream>
using namespace std;

class C1 // private权限
{
  int m_A; // 默认是私有权限
};

struct C2 // public权限
{
  int m_A; // 默认是公共权限
};

int main()
{
  // struct和class区别
  // struct默认权限是公共public
  // class默认权限是私有private

  C1 c1;
  // c1.m_A = 10; // 错误，访问权限是私有
  // 在class里默认权限为私有，因此类外不可以访问

  C2 c2;
  c2.m_A = 10;            // 正确，访问权限是公共
  cout << c2.m_A << endl; // 在struct中默认的权限为公共，因此可以访问

  return 0;
}