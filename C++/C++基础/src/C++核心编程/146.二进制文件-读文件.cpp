#include <iostream>
#include <fstream> //1、包含头文件
#include <string>
using namespace std;

class Person
{
public:
	char m_Name[64]; // 姓名
	int m_Age;		 // 年龄
};

void test01()
{
	// 2、创建流对象
	// ifstream ifs;
	ifstream ifs("person.txt", ios::in | ios::binary);
	// 3、打开文件，判断文件是否打开成功
	// ifs.open("person.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
	}
	// 4、读文件
	Person p;
	ifs.read((char *)&p, sizeof(Person)); //(char *)强转
	cout << "姓名：" << p.m_Name << "，年龄：" << p.m_Age << endl;
	// 5、关闭文件
	ifs.close();
}

int main()
{
	test01();
	system("pause");
	return 0;
}