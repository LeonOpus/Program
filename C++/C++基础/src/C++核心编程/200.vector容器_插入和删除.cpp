#include <iostream>
#include <vector>
using namespace std;

/*vector容器插入删除操作
1.push_back(ele);//尾部插入元素ele
2.pop_back();//删除最后一个元素
3.insert(const_iterator pos, ele);//在指定位置pos前插入元素ele
4.insert(const_iterator pos, int count,ele);//在指定位置pos前插入count个元素ele
5.erase(const_iterator pos);//删除指定位置的元素
6.erase(const_iterator start, const_iterator end);//删除从start到end之间的元素
7.clear();//删除容器中所有元素
*/

void printVector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test01()
{ // 插入和删除
    vector<int> v1;

    // 尾部插入
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    printVector(v1); // 输出结果10 20 30 40 50

    // 尾部删除
    v1.pop_back();
    printVector(v1); // 输出结果10 20 30 40

    // 插入，第一个参数是迭代器
    v1.insert(v1.begin(), 100);
    printVector(v1); // 输出结果100 10 20 30 40

    v1.insert(v1.begin(), 2, 1000);
    printVector(v1); // 输出结果1000 1000 100 10 20 30 40

    // 删除，参数也是迭代器
    v1.erase(v1.begin());
    printVector(v1); // 输出结果1000 100 10 20 30 40

    // 清空
    // v1.erase(v1.begin(), v1.end());
    v1.clear();
    printVector(v1);
}

int main()
{
    test01();
    return 0;
}