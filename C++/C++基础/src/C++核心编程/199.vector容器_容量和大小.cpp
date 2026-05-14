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

// vector容器的容量和大小操作
void test01()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    if (v1.empty())
    { // 为真 代表v1为空
        cout << "v1为空" << endl;
    }
    else
    {
        cout << "v1不为空" << endl;
        cout << "v1的容量为：" << v1.capacity() << endl;
        cout << "v1的大小为：" << v1.size() << endl;
    }

    // resize 重新指定容器的大小
    v1.resize(15, 100); // 重新指定容器的大小为15，若指定的大小比原大小大，则默认用0填充新位置，若指定的大小比原大小小，则超出部分元素被删除
    printVector(v1);    // 0 1 2 3 4 5 6 7 8 9 100 100 100 100 100

    // resize 重新指定容器的大小
    v1.resize(5);    // 重新指定容器的大小为5,若指定的大小比原大小小,则超出部分元素被删除
    printVector(v1); // 0 1 2 3 4
}

int main()
{
    test01();
    return 0;
}