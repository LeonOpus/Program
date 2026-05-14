#include <iostream>
#include <vector>
using namespace std;

// vector容器-预留空间
void test01()
{
	vector<int> v;
	v.reserve(100000); // 使用reserve预留空间
	int num = 0;	   // 统计重新分配内存的次数
	int *p = NULL;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
		if (p != &v[0])
		{ // 指针是否指向新的地址
			p = &v[0];
			num++;
		}
	}
	cout << "num = " << num << endl; // num = 1
}

int main()
{
	test01();
	return 0;
}