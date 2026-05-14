#include <iostream> //占位参数
using namespace std;

// 语法：返回值类型 函数名 (数据类型) {}
// 目前阶段的占位参数，我们还用不到，后面课程中会用到。
// 函数占位参数 ，占位参数也可以有默认参数

// void func(int a, int)
void func(int a, int = 10)
{
    cout << "this is func !" << endl;
}

int main()
{
    func(10, 10); // 占位参数必须填补
    func(10);     // 占位参数可以填补
    return 0;
}