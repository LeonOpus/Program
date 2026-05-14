#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> //内建函数对象头文件
using namespace std;

// 内建函数对象-逻辑仿函数
// logical_not：逻辑非仿函数

void test01()
{
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    for (vector<bool>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " "; // 1 0 1 0
    }
    cout << endl;

    // 利用逻辑非将容器v搬运到容器v2中，并执行取反操作(并执行逻辑非运算)
    vector<bool> v2;
    v2.resize(v.size());
    transform(v.begin(), v.end(), v2.begin(), logical_not<bool>()); // 搬运算法
    for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
    {
        cout << *it << " "; // 0 1 0 1
    }
    cout << endl;
}

int main()
{
    test01();
    return 0;
}