#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 仿函数返回值类型是bool数据类型，称为谓词。
// 二元谓词

class MyCompare
{
public:
    bool operator()(int va11, int val2)
    {                       //(int num1, int num2)
        return va11 > val2; // num1 > num2;
    }
};

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);

    sort(v.begin(), v.end()); // 默认从小到大
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    cout << "----------------------------" << endl;

    // 使用函数对象改变算法策略，变为排序规则为从大到小
    sort(v.begin(), v.end(), MyCompare());
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