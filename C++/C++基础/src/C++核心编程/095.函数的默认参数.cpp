#include <iostream>
using namespace std;

// 函数默认参数
// 如果我们自己传入数据，就用自己的数据；如果没有，那么用默认值。
// 语法：返回值类型 函数名(形参 = 默认值) {}
int func1(int a, int b = 20, int c = 30)
{
    return a + b + c;
}

// 注意事项：
// 1.如果某个位置已经有了默认参数(参数有默认值)，那么从这个位置往后，从左向右都必须要有默认值。
// 2.如果函数声明有默认参数值，函数实现的时候就不能有默认参数。声明和实现只能有一个有默认参数。
int func2(int a = 10, int b = 10);
int func2(int a, int b)  //(int a = 10, int b = 10)报错
{
    return a + b;
}

int main()
{
    cout << "ret = " << func1(10) << endl;      // ret = 60
    cout << "ret = " << func1(10, 20) << endl;  // ret = 60
    cout << func2() << endl;                    // 20
    cout << func2(1, 2) << endl;                // 3
    return 0;
}