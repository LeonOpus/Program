#include <iostream>
using namespace std;
// 成员变量和成员函数是分开存储的
class Person
{
public:
    Person()
    {
        mA = 0;
    }
    int mA;        // 非静态成员变量占对象空间，属于类的对象上
    static int mB; // 静态成员变量不占对象空间，不属于类的对象上
    void func()
    { // 非静态函数也不占对象空间，所有函数共享一个函数实例，不属于类的对象上
        cout << "mA：" << this->mA << endl;
    }
    static void sfunc() {} // 静态成员函数也不占对象空间，不属于类的对象上
};

int Person::mB = 0;

void test01()
{
    Person p;
    // 空对象占用内存空间为：1
    // C++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置。
    // 每个空对象也应该有一个独一无二的内存地址
    cout << "size of p = " << sizeof(p) << endl;
}

int main()
{
    cout << sizeof(Person) << endl;
    return 0;
}