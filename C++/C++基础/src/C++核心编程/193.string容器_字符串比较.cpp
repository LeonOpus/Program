#include <iostream>
#include <string>
using namespace std;

void test01()
{ // 字符串比较
	string str1 = "hello";
	string str2 = "xello";
	if (str1.compare(str2) == 0)
	{
		cout << "str1 等于 str2" << endl;
	}
	else if (str1.compare(str2) > 0)
	{
		cout << "str1 大于 str2" << endl;
	}
	else
	{
		cout << "str1 小于 str2" << endl;
	}
}

void test02()
{ // 字符串比较
	string s1 = "hello";
	string s2 = "aello";
	int ret = s1.compare(s2);
	if (ret == 0)
	{
		cout << "s1 等于 s2" << endl;
	}
	else if (ret > 0)
	{
		cout << "s1 大于 s2" << endl;
	}
	else
	{
		cout << "s1 小于 s2" << endl;
	}
}

int main()
{
	test01();
	test02();
	return 0;
}