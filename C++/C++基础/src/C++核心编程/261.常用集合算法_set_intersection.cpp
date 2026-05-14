#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 常用集合算法-set_intersection

void myPrint(int val)
{
    cout << val << " ";
}

class myPrint
{
public:
    void operator()(int val)
    {
        cout << val << " ";
    }
};

void test01()
{
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);     // 0 ~ 9
        v2.push_back(i + 5); // 5 ~ 14
    }

    vector<int> vTarget;
    // 目标容器需要提前开辟空间
    // 最特殊情况：大容器包含小容器。开辟空间：取小容器的size即可。
    vTarget.resize(min(v1.size(), v2.size())); // 取两个里面较小的值给目标容器开辟空间

    // 获取交集，返回目标容器的最后一个元素的迭代器地址
    vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), itEnd, myPrint); // 5 6 7 8 9
    cout << endl;
}

int main()
{
    test01();
    return 0;
}