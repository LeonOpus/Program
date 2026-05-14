#include <iostream>
using namespace std;

// 拷贝构造函数调用时机
// 1、使用一个已经创建完毕的对象来初始化一个新对象；
// 2、值传递的方式给函数参数传值；
// 3、值方式返回局部对象。

class Person
{
public:
    Person()
    {
        cout << "Person默认(无参)构造函数调用!" << endl;
        mAge = 0;
    }
    Person(int age)
    {
        cout << "Person有参构造函数调用!" << endl;
        mAge = age;
    }
    Person(const Person &p)
    {
        cout << "Person拷贝构造函数调用!" << endl;
        mAge = p.mAge;
    }
    // 析构函数在释放内存之前调用
    ~Person() { cout << "Person析构函数调用!" << endl; }

public:
    int mAge;
};

// 1.使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{
    Person man(100);      // p对象已经创建完毕
    Person newman(man);   // 调用拷贝构造函数
    Person newman2 = man; // 拷贝构造
    // Person newman3;
    // newman3 = man; //不是调用拷贝构造函数，赋值操作

    Person p1(20);
    Person p2(p1);
    cout << "P2的年龄为：" << p2.mAge << endl;
}

// 2.值传递的方式给函数参数传值
// 相当于：Person p1 = p;
void doWork(Person p1) {}
void test02()
{
    Person p;  // 无参构造函数
    doWork(p); // 拷贝新数据
}

// 3.以值方式返回局部对象
Person doWork2()
{
    Person p1;
    cout << (int *)&p1 << endl;
    return p1;
}
void test03()
{
    Person p = doWork2();
    cout << (int *)&p << endl;
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}