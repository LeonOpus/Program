#include <iostream>
#include <fstream> //【1】包含头文件
#include <string>
using namespace std;

void test01()
{
	// 【2】创建流对象
	ifstream ifs;

	// 【3】打开文件，并且判断文件是否打开成功
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}

	// 【4】读取文件数据
	// 第1种方式
	// char buf[1024] = { 0 };//字符数组
	// while (ifs >> buf) {
	//	cout << buf << endl;
	// }

	// 第2种方式
	// char buf[1024] = { 0 };
	// while (ifs.getline(buf, sizeof(buf))) {
	//	cout << buf << endl;
	// }

	// 第3种方式
	// string buf;
	// while (getline(ifs, buf)) {
	//	cout << buf << endl;
	// }

	// 第4种方式
	char c;
	while ((c = ifs.get()) != EOF)
	{ // eof：end of file
		cout << c;
	}

	// 【5】关闭文件
	ifs.close();
}

int main()
{
	test01();
	system("pause");
	return 0;
}