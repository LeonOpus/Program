#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
// 常用排序算法-sort

void myPrint(int val)
{
    cout << val << " ";
}

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(20);
    v.push_back(40);

    // 利用sort进行升序，sort默认从小到大排序
    sort(v.begin(), v.end());
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;

    // 改变为降序，从大到小排序
    sort(v.begin(), v.end(), greater<int>());
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;
}

int main()
{
    test01();
    return 0;
}