#include <iostream>//类模板分文件编写问题以及解决
using namespace std;

//#include "person.h"

//第一种解决方式：直接包含源文件
// #include "person.cpp"//解决方式1，直接包含cpp源文件

//解决方式2，将声明和实现写到一起，文件后缀名改为.hpp
//第二种解决方式：将.h和.cpp中的内容写到一起，将后缀名改为.hpp文件
#include "person.hpp"

// //类模板分文件编写问题以及解决
// template <class T1, class T2>
// class Person {
//     public:
//         Person(T1 name, T2 age);
//         void showPerson();
//         T1 m_Name;
//         T2 m_Age;
// };

// template <class T1, class T2>
// Person<T1, T2>::Person(T1 name, T2 age) {
//     this->m_Name = name;
//     this->m_Age = age;
// }

// template <class T1, class T2>
// void Person<T1, T2>::showPerson() {
//     cout << "姓名： " << this->m_Name << " 年龄： " << this->m_Age << endl;
// }

void test01() {
    Person<string, int> p1("Tom", 10);
    p1.showPerson();
    Person<string, int> p2("Jerry", 18);
    p2.showPerson();

}

int main() {
    test01();
    return 0;
}