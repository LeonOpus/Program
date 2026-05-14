#include <iostream> //string求子串
#include <string>
using namespace std;

void test01()
{
	 // string求子串
	string str = "abcdefg";
	string subStr = str.substr(1, 3);
	cout << "subStr = " << subStr << endl;

	// 实用操作：从邮件地址中获取用户名信息
	string email = "hello@sina.com";
	int pos = email.find("@");
	string userName = email.substr(0, pos);
	cout << "userName：" << userName << endl;
}

void test02()
{ // 实用操作
	string email = "zhangsan@sina.com";
	// 从邮件地址中获取用户名信息
	int pos = email.find("@"); // 8
	cout << pos << endl;
	string usrName = email.substr(0, pos);
	cout << usrName << endl;
}

int main()
{
	test01();
	test02();
	return 0;
}