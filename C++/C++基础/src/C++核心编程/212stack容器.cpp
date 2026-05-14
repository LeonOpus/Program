#include <iostream>
#include <stack> //栈stack容器
using namespace std;

void test01()
{ // 栈容器常用接口
    // 特点：符合先进后出数据结构
    stack<int> s; // 创建栈容器，栈容器必须符合先进后出

    // 向栈中添加元素，叫做：压栈、入栈
    // 入栈
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    cout << "栈的大小：" << s.size() << endl; // 4

    // 只要栈不为空，查看栈顶，并且执行出栈操作
    while (!s.empty())
    {
        // 查看栈顶元素
        cout << "栈顶元素为：" << s.top() << endl; // 输出栈顶元素
        s.pop();                                   // 出栈//弹出栈顶元素
    } // 40 30 20 10
    cout << "栈的大小：" << s.size() << endl; // 0
}

int main()
{
    test01();
    return 0;
}