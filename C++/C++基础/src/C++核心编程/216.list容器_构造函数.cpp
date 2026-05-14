#include <iostream>
#include <list>
using namespace std;
// list容器_构造函数

void printList(const list<int> &L)
{
    for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test01()
{
    // 创建list容器
    list<int> L1; // 默认构造

    // 添加元素
    L1.push_back(10);
    L1.push_back(20);
    L1.push_back(30);
    L1.push_back(40);
    L1.push_back(50);
    L1.push_back(60);
    L1.push_back(70);
    L1.push_back(80);
    L1.push_back(90);



    // 打印容器
    printList(L1); // 10 20 30 40

    // 区间方式构造
    list<int> L2(L1.begin(), L1.end());
    printList(L2); // 10 20 30 40

    // 拷贝构造
    list<int> L3(L2);
    printList(L3); // 10 20 30 40

    // n个elem
    list<int> L4(10, 11);
    printList(L4); // 11 11 11 11 11 11 11 11 11 11
}

int main()
{
    test01();

    return 0;
}