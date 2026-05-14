#include <iostream> //示例1：静态成员变量
using namespace std;

class Person {
public:
  // 静态成员变量
  static int m_A;
  // 静态成员变量特点：
  // 1、在编译阶段分配内存
  // 2、类内声明，类外初始化
  // 3、所有对象共享同一份数据
private:
  static int m_B; // 静态成员变量也是有访问权限的
};

// 静态成员变量：类内声明，类外初始化
int AAA = 10;          // 全局变量
int Person::m_A = 100; // Person的静态成员变量
int Person::m_B = 222; // Person的静态成员变量

void test01() {
  // 静态成员变量不属于某个对象上，所有对象都共享同一份数据
  // 因此静态成员变量有两种访问方式

  // 访问方式
  // 1、非静态成员变量 通过实例化对象进行访问
  Person p1;
  p1.m_A = 100;
  cout << "p1.m_A = " << p1.m_A << endl;

  Person p2;
  p2.m_A = 200;
  cout << "p1.m_A = " << p1.m_A << endl; // 共享同一份数据
  cout << "p2.m_A = " << p2.m_A << endl;

  // 2、 静态成员变量 通过类名进行访问
  cout << "m_A = " << Person::m_A << endl;

  // 私有权限访问不到，类外访问不到私有静态成员变量
  // cout << "m_B = " << Person::m_B << endl;
}

int main() {
  test01();
  return 0;
}