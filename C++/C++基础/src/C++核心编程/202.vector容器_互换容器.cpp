#include <iostream> //vector容器互换
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

// 1.基本使用
void test01()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    cout << "交换前：" << endl;
    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    vector<int> v2;
    for (int i = 10; i > 0; i--)
    {
        v2.push_back(i);
    }
    printVector(v2); // 10 9 8 7 6 5 4 3 2 1

    cout << "交换后：" << endl;
    v1.swap(v2);     // 互换容器
    printVector(v1); // 10 9 8 7 6 5 4 3 2 1
    printVector(v2); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;
}

// 2.实际用途-利用swap可以收缩内存空间
void test02()
{
    vector<int> v;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
    }
    cout << "v的容量为：" << v.capacity() << endl; // v的容量为：131072
    cout << "v的大小为：" << v.size() << endl
         << endl; // v的大小为：100000

    v.resize(3);                                   // 重新指定大小
    cout << "v的容量为：" << v.capacity() << endl;   // v的容量为：131072
    cout << "v的大小为：" << v.size() << endl
         << endl;   // v的大小为：3

    // 利用swap收缩内存，让v当前占用的空间与实际数据量匹配
    vector<int>(v).swap(v); // 匿名对象

    cout << "v的容量为：" << v.capacity() << endl; // v的容量为：3
    cout << "v的大小为：" << v.size() << endl;     // v的大小为：3
}

int main()
{
    test01();
    test02();
    return 0;
}