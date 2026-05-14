#include <iostream>
#include <string>
using namespace std;

//结构体指针
//1、定义学生结构体
struct student
{				 //成员列表
	string name; //姓名
	int age;	 //年龄
	int score;	 //分数
};

int main()
{
	//2、创建学生结构体变量
	// struct student stu = {"张三", 25, 100}; //struct可以省略
	student stu = {"张三", 25, 99}; //struct可以省略

	//3、通过指针指向结构体变量
	// struct student *p = &stu; //struct可以省略
	student *p = &stu; //struct可以省略

	//结构体变量，可以直接通过.来访问
	cout << "姓名：" << stu.name << "\t年龄：" << stu.age << "\t分数：" << stu.score << endl;

	//4、通过指针访问结构体变量中的数据
	p->score = 66; //指针通过 -> 操作符可以访问成员

	//通过结构体指针访问结构体中的属性，需要利用“->”
	cout << "姓名：" << p->name << "\t年龄：" << p->age << "\t分数：" << p->score << endl;

	system("pause");
	return 0;
}