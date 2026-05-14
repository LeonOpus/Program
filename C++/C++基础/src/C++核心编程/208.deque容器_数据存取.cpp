#include <iostream>
#include <deque> //deque容器_数据存取
using namespace std;

void printDeque(const deque<int> &d)
{
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// 数据存取
void test01()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_front(100);
    d.push_front(200);
    d.push_front(300);

    // 1.通过[]方式访问元素
    for (int i = 0; i < d.size(); i++)
    {
        cout << d[i] << " ";
    }
    cout << endl; // 300 200 100 10 20 30

    // 2.通过at方式访问元素
    for (int i = 0; i < d.size(); i++)
    {
        cout << d.at(i) << " ";
    }
    cout << endl; // 300 200 100 10 20 30

    // 获取首尾元素
    cout << "第一个元素front为：" << d.front() << endl; // 300
    cout << "最后一个元素back为：" << d.back() << endl; // 30
}

int main()
{
    test01();
    return 0;
}