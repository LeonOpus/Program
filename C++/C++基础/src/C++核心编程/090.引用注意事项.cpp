#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int b = 20;
    // int &c = a + b;   //错误，引用必须初始化
    int &c = a; // 一旦初始化后，就不能改变引用的对象
    c = b;      // 这个是赋值，不是改变引用的对象
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "a的地址=" << &a << endl;
    cout << "b的地址=" << &b << endl;
    cout << "c的地址=" << &c << endl;
    return 0;
}