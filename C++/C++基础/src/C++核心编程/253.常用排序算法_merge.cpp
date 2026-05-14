#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 常用排序算法-merge

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

// 常用排序算法-merge
void test01()
{
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 1);
    }

    vector<int> vTarget; // 目标容器

    // 提前给目标容器分配空间，目标容器需要提前开辟空间
    vTarget.resize(v1.size() + v2.size());
    // 合并，需要两个有序序列
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), vTarget.end(), myPrint);
    cout << endl;
}

int main()
{
    test01();
    return 0;
}