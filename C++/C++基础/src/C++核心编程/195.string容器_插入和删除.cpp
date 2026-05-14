#include <iostream>
#include <string>
using namespace std;

void test01()
{ // 字符串插入和删除
	string str = "hello";
	str.insert(1, "111");			 // 插入
	cout << "str = " << str << endl; // str = h111ello

	str.erase(1, 3);				 // 删除，从1号位置开始3个字符
	cout << "str = " << str << endl; // str = hello
}

int main()
{
	test01();
	return 0;
}