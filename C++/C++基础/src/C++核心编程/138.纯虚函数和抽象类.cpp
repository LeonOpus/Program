#include <iostream>
using namespace std;

class Base
{
public:
    // 类中只要有一个纯虚函数就称为抽象类
    // 抽象类特点：1、抽象类无法实例化对象
    // 2、抽象类的子类必须要重写父类中的纯虚函数，否则也属于抽象类
    // 子类必须重写父类中的纯虚函数，否则也属于抽象类
    virtual void func() = 0; // 纯虚函数
};

class Son : public Base
{
public:
    virtual void func()
    { // 重写
        cout << "func调用！" << endl;
    };
};

void test01()
{
    // Base b;//抽象类无法实例化对象
    // new Base;//抽象类无法实例化对象
    Son s;                // 子类必须重写父类中的纯虚函数，否则无法实例化对象
    Base *base = new Son; // 多态
    base->func();

    Base *base = NULL;
    // base = new Base;//错误，抽象类无法实例化对象
    base = new Son;
    base->func();
    delete base; // 记得销毁
}

int main()
{
    test01();
    system("pause");
    return 0;
}