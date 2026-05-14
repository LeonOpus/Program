#include <iostream>
using namespace std;

class Person
{
public:
  // 传统方式初始化
  // Person(int a, int b, int c) {
  //	m_A = a;
  //	m_B = b;
  //	m_C = c;
  // }

  // 初始化列表方式初始化属性
  // Person() :m_A(1), m_B(2), m_C(3) {}
  Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c) {}
  void PrintPerson()
  {
    cout << "mA：" << m_A << endl;
    cout << "mB：" << m_B << endl;
    cout << "mC：" << m_C << endl;
  }

public:
  int m_A;
  int m_B;
  int m_C;
};

void test01()
{
  Person p(10, 20, 30);
  cout << "m_A = " << p.m_A << endl;
  cout << "m_B = " << p.m_B << endl;
  cout << "m_C = " << p.m_C << endl;
}

int main()
{
  // 初始化列表方式初始化属性
  Person p(1, 2, 3);
  // Person p(1, 2, 3);
  // p.PrintPerson();
  // 调用 test01 函数以输出 10, 20, 30
  test01();
  return 0;
}