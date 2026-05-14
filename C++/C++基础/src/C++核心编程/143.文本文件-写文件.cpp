#include <iostream>
#include <fstream> //1、包含头文件<fstream>
using namespace std;

void test01()
{
	// 2、创建流对象
	ofstream ofs;
	// 3、指定打开方式
	ofs.open("test.txt", ios::out);
	// 4、写内容
	ofs << "姓名：张三" << endl;
	ofs << "性别：男" << endl;
	ofs << "年龄：18" << endl;
	// 5、关闭文件
	ofs.close();
}
int main()
{
	test01();
	return 0;
}