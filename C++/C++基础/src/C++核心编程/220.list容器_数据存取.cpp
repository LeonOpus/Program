#include <iostream>
#include <list>
using namespace std;

// list容器-数据存取
void test01()
{
    list<int> L1;
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);

    // L1[0]不可以用[]方式访问list容器中的元素
    // L1.at(0)不可以用at方式访问list容器中的元素
    // 原因是list容器的迭代器是双向迭代器，不支持随机访问

    cout << "第一个元素为：" << L1.front() << endl;
    cout << "最后一个元素为：" << L1.back() << endl;

    // 验证迭代器是不支持随机访问的
    list<int>::iterator it = L1.begin();
    // it++;//支持双向
    it--;
    // it = it + 1;//不支持随机访问

    // cout << L1.at(0) << endl;//错误，不支持at访问方式
    // cout << L1[0] << endl; //错误，不支持[]访问方式
    cout << "第一个元素为：" << L1.front() << endl;
    cout << "最后一个元素为：" << L1.back() << endl;

    // list容器的迭代器是双向迭代器，不支持随机访问
    // list<int>::iterator it = L1.begin();
    // it = it + 1;//错误，不可以跳跃访问，即使是+1
}

int main()
{
    test01();
    return 0;
}