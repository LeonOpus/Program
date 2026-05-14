#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// vector容器_赋值操作
void test01()
{
    vector<int> v1; // 默认构造
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    // 赋值方式1: operator=
    vector<int> v2;
    v2 = v1;
    printVector(v2); // 0 1 2 3 4 5 6 7 8 9

    // 赋值方式2: assign
    vector<int> v3;
    v3.assign(v1.begin(), v1.end());
    printVector(v3); // 0 1 2 3 4 5 6 7 8 9

    // 赋值方式3: n个elem方式赋值
    vector<int> v4;
    v4.assign(10, 100);
    printVector(v4); // 100 100 100 100 100 100 100 100 100 100
}

int main()
{
    test01();
    return 0;
}