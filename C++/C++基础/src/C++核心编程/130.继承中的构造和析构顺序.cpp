#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base构造函数!" << endl;
    }
    ~Base()
    {
        cout << "Base析构函数!" << endl;
    }
};

class Son : public Base
{
public:
    Son()
    {
        cout << "Son构造函数!" << endl;
    }
    ~Son()
    {
        cout << "Son析构函数!" << endl;
    }
};

void test01()
{
    // Base b;
    // 继承中的构造和析构顺序如下：先构造父类，再构造子类，析构的顺序与构造的顺序相反。
    Son s; // 继承中，先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反。
}

int main()
{
    test01();
    return 0;
}
/*
Base构造函数!
Son构造函数!
Son析构函数!
Base析构函数!
请按任意键继续. . .
*/