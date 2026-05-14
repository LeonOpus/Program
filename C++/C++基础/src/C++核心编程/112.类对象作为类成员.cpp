#include <iostream> //类对象作为类成员
#include <string>   //字符串头文件
using namespace std;

// 类对象作为类成员
// 手机类
class Phone {
public:
  Phone(string name) {
    m_PhoneName = name;
    cout << "Phone构造函数调用" << endl;
  }
  ~Phone() { cout << "Phone析构函数调用" << endl; }
  string m_PhoneName; // 手机品牌名称
};

// 人类
class Person {
public:
  // 初始化列表可以告诉编译器调用哪一个构造函数
  //  Phone m_Phone = pName;//隐式转换法
  Person(string name, string pName) : m_Name(name), m_Phone(pName) {
    cout << "Person构造函数调用" << endl;
  }

  ~Person() { cout << "Person析构函数调用" << endl; }

  void playGame() {
    cout << m_Name << "使用" << m_Phone.m_PhoneName << "牌手机！" << endl;
  }

  string m_Name; // 姓名
  Phone m_Phone; // 手机
};

// 当其他类对象作为本类成员，构造时候先构造类对象再构造自身，析构的顺序与构造相反.
void test01() {
  // 当类中成员是其他类对象时，我们称该成员为“对象成员”。
  // 构造的顺序是 ：先调用对象成员的构造，再调用本类构造；
  // 析构顺序与构造相反。
  Person p("张三", "苹果X");
  cout << p.m_Name << "拿着" << p.m_Phone.m_PhoneName << endl;
  p.playGame();
}

int main() {
  test01();
  return 0;
}