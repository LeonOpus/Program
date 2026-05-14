#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        m_A = 100;
    }
    void func()
    {
        cout << "Base - func()调用！" << endl;
    }
    void func(int a)
    {
        cout << "Base - func(int a)调用！" << endl;
    }

public:
    int m_A;
};

class Son : public Base
{
public:
    Son()
    {
        m_A = 200;
    }
    // 当子类与父类拥有同名的成员函数，子类会隐藏父类中所有版本的同名成员函数
    // 如果想访问父类中被隐藏的同名成员函数，需要加父类的作用域
    void func()
    {
        cout << "Son - func()调用！" << endl;
    }

public:
    int m_A;
};

void test01()
{ // 同名成员属性处理方式
    Son s;
    cout << "Son下的m_A = " << s.m_A << endl;
    // 如果通过子类对象访问到父类中同名成员，需要加作用域
    cout << "Base下的m_A = " << s.Base::m_A << endl; // s.Base::父类作用域
}

void test02()
{ // 同名成员函数处理方式
    Son s;
    s.func();       // 直接调用，调用是子类中的同名成员
    s.Base::func(); // 如何调用到父类中同名成员函数?
    // 如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类中所有同名成员函数
    s.Base::func(10); // 如果想访问到父类中被隐藏的同名成员函数，需要加作用域
}

int main()
{
    test01();
    test02();
    return EXIT_SUCCESS;
}