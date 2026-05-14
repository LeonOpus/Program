#include <iostream>
#include <map>
using namespace std;

class MyCompare
{
public:
	bool operator()(int v1, int v2) const
	{ // 降序
		return v1 > v2;
	}
};

// map容器-排序
void test01()
{
	map<int, int, MyCompare> m;
	// 默认从小到大排序，利用仿函数实现从大到小排序
	m.insert(make_pair(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(make_pair(5, 50));
	m.insert(make_pair(3, 30));
	m.insert(make_pair(4, 40));
	for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
}

int main()
{
	test01();
	return 0;
}