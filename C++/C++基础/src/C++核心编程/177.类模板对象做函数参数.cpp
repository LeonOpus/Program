#include <iostream>
#include <string>
using namespace std;

//类模板对象做函数参数
//1、指定传入类型
//2、参数模板化
//3、整个类模板化

//类模板
//template <class T1, class T2>
// class Person {
//     public:
//         Person(T1 name, T2 age) {
//             this->mName = name;
//             this->mAge = age;
//         }
//         void showPerson() {
//             cout << "姓名name：" << this->mName << "，年龄age：" << this->mAge << endl;
//         }
//     public:
//         T1 mName;
//         T2 mAge;
// };
template <class NameType, class AgeType = int>
class Person {
    public:
        Person(NameType name, AgeType age) {
            this->mName = name;
            this->mAge = age;
        }
        void showPerson() {
            cout << "姓名name：" << this->mName << "，年龄age：" << this->mAge << endl;
        }
    public:
        NameType mName;
        AgeType mAge;
};

//1、指定传入的类型
void printPerson1(Person<string, int> &p) {
    p.showPerson();
}

void test01() {
    Person<string, int> p("孙悟空", 100);
    printPerson1(p);
    cout << endl;
}

//2、参数模板化
template <class T1, class T2>
void printPerson2(Person<T1, T2> &p) {
    p.showPerson();
    cout << "T1的类型为：" << typeid(T1).name() << endl;//T1的类型为：NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    cout << "T2的类型为：" << typeid(T2).name() << endl;//T2的类型为：i
}

void test02() {
    Person<string, int> p("猪八戒", 90);
    printPerson2(p);
    cout << endl;
}

//3、整个类模板化
template <class T>
void printPerson3(T &p) {
    cout << "T的数据类型为：" << typeid(T).name() << endl;
    p.showPerson();
}

void test03() {
    Person<string, int> p("唐僧", 30);
    printPerson3(p);//T的类型为：6PersonINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEiE
    cout << endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}