#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

// list容器_反转和排序

void printList(const list<int> &L)
{
    for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// bool myCompare(int val1, int val2) {
// 	return val1 > val2;
// }
bool myCompare(int v1, int v2)
{
    // 降序：让第一个数 > 第二个数
    return v1 > v2;
}

// 反转
void test01()
{
    list<int> L1;
    L1.push_back(20);
    L1.push_back(10);
    L1.push_back(50);
    L1.push_back(40);
    L1.push_back(30);
    cout << "反转前：" << endl;
    printList(L1);

    // 反转
    L1.reverse(); // 反转容器元素
    cout << "反转后：" << endl;
    printList(L1);
}

// 排序
void test02()
{
    list<int> L1;
    L1.push_back(20);
    L1.push_back(10);
    L1.push_back(50);
    L1.push_back(40);
    L1.push_back(30);

    // 排序
    cout << "排序前：" << endl;
    printList(L1);

    // list不支持随机访问迭代器，不能使用标准算法
    // 不支持随机访问迭代器，需要使用内部提供的算法
    // sort(L1.begin(), L1.end());

    L1.sort(); // 默认排序规则：从小到大排序
    cout << "排序后：" << endl;
    printList(L1);

    L1.sort(myCompare);
    printList(L1);
}

// 反转和排序
void test03()
{
    list<int> L;
    L.push_back(90);
    L.push_back(30);
    L.push_back(20);
    L.push_back(70);
    printList(L);

    // 反转容器元素
    L.reverse();
    printList(L);

    // 排序
    L.sort(); // 默认的排序规则：从小到大
    printList(L);

    L.sort(myCompare); // 指定规则：从大到小
    printList(L);
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}