#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> //内建函数对象头文件
using namespace std;

// 内建函数对象-关系仿函数
// greater：大于仿函数

class MyCompare
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(40);
    v.push_back(20);
    v.push_back(50);

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 自己实现仿函数
    // sort(v.begin(), v.end(), MyCompare());//降序

    // greater<int>()内建函数对象#include <functional>
    // STL内建仿函数-大于仿函数
    sort(v.begin(), v.end(), greater<int>());
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    test01();
    return 0;
}