#include <iostream>
using namespace std;

class Person
{
public:
    Person(int age)
    {
        // 当形参和成员变量同名时，可用this指针来区分【1、解决名称冲突】
        this->age = age; // this指针指向被调用的成员函数所属的对象。
    }
    Person &PersonAddAge(Person p)
    {
        // 返回本体用引用方式返回
        this->age += p.age;
        // this指向p2的指针，而*this指向的就是p2这个对象本体
        return *this; // 【2、返回对象本身用“*this”】
    }
    int age;
};

void test01()
{
    Person p1(10);
    cout << "p1.age = " << p1.age << endl;

    Person p2(10);
    // 链式编程思想
    p2.PersonAddAge(p1).PersonAddAge(p1).PersonAddAge(p1);
    cout << "p2的年龄p2.age = " << p2.age << endl; // 20
}

int main()
{
    test01();
    return 0;
}