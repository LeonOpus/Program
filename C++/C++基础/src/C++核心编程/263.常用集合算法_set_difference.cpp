#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 常用集合算法-set_difference

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

void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	// 创建目标容器
	vector<int> vTarget;
	// 给目标容器开辟空间
	// 最特殊情况  两个容器没有交集 取两个容器中大的size作为目标容器开辟空间
	vTarget.resize(max(v1.size(), v2.size())); // 取两个里面较大的值给目标容器开辟空间

	// 返回目标容器的最后一个元素的迭代器地址
	cout << "v1和v2的差集为：" << endl;

	vector<int>::iterator itEnd = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

	for_each(vTarget.begin(), itEnd, myPrint);
	cout << endl;

	cout << "v2和v1的差集为：" << endl;
	itEnd = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), vTarget.begin());

	for_each(vTarget.begin(), itEnd, myPrint);
	cout << endl;
}

int main()
{
	test01();
	return 0;
}