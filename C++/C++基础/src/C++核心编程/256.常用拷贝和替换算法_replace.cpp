#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 常用拷贝和替换算法-replace

class MyPrint
{
public:
    void operator()(int val)
    {
        cout << val << " ";
    }
};

void test01()
{
    vector<int> v;
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    v.push_back(30);
    v.push_back(40);
    v.push_back(20);
    v.push_back(10);
    v.push_back(20);

    cout << "替换前：" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;
    // 将容器中的20替换成2000
    cout << "替换后：" << endl;
    replace(v.begin(), v.end(), 20, 2000);
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;
}

int main()
{
    test01();
    return 0;
}