#include <iostream> //string字符存取
#include <string>
using namespace std;

void test01()
{ // string字符存取
	string str = "hello world";
	// cout << "str = " << str << endl;

	// 1、通过[]访问单个字符
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i] << " ";
	}
	cout << endl;

	// 2、通过at方式访问单个字符
	for (int i = 0; i < str.size(); i++)
	{
		cout << str.at(i) << " ";
	}
	cout << endl;

	// 字符修改(修改单个字符)
	str[0] = 'x';
	cout << "str = " << str << endl; // xello
	str.at(1) = 'x';
	cout << "str = " << str << endl; // xxllo
}

int main()
{
	test01();
	return 0;
}