#include <iostream> //二进制文件-写文件
#include <fstream>	//1、包含头文件
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
	// 2、创建输出流对象
	ofstream ofs("person.txt", ios::out | ios::binary);
	// 3、打开文件
	// ofs.open("person.txt", ios::out | ios::binary);
	// 4、写文件
	Person p = {"张三", 18};
	ofs.write((const char *)&p, sizeof(p)); // 强转
	// 5、关闭文件
	ofs.close();
}

int main()
{
	test01();
	return 0;
}