#include <iostream>
#include <string>
using namespace std;

/*函数对象（仿函数）
- 1.函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值；
- 2.函数对象超出普通函数的概念，函数对象可以有自己的状态；
- 3.函数对象可以作为参数传递。
*/

// 1、函数对象在使用时，可以像普通函数那样调用，可以有参数，可以有返回值。
class MyAdd
{
public:
    int operator()(int v1, int v2)
    {
        return v1 + v2;
    }
};
void test01()
{
    MyAdd myAdd; // 函数对象
    cout << myAdd(10, 10) << endl;
}

// 2、函数对象超出普通函数的概念，函数对象可以有自己的状态。
class MyPrint
{
public:
    MyPrint()
    {
        this->count = 0; // count = 0;
    }
    void operator()(string test)
    {
        cout << test << endl;
        this->count++; // count++;统计使用次数
    }
    int count; // 内部自己的状态
};
void test02()
{
    MyPrint myPrint;
    myPrint("hello world！");
    myPrint("hello world！");
    myPrint("hello world！");
    myPrint("hello world！");
    cout << "myPrint()调用次数为：" << myPrint.count << endl; // 4
}

// 3、函数对象可以作为参数传递。
void doPrint(MyPrint &mp, string test)
{
    mp(test);
}
void test03()
{
    MyPrint myPrint;
    doPrint(myPrint, "Hello c++");
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}