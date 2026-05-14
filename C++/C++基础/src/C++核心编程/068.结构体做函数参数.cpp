#include <iostream>
#include <string>
using namespace std;

// 定义学生结构体
struct student
{
	// 成员列表
	string name; // 姓名
	int age;	 // 年龄
	int score;	 // 分数
};

//
// 1、值传递
void printStudent1(struct student stu) //(student stu)
{
	stu.age = 28; // 修改属性
	cout << "1子函数中\t姓名：" << stu.name << "\t年龄：" << stu.age << "\t分数：" << stu.score << endl;
}

// 2、地址传递
void printStudent2(struct student *stu) // 用指针*stu接收地址
{
	stu->age = 28;
	cout << "2子函数中\t姓名：" << stu->name << "\t年龄：" << stu->age << "\t分数：" << stu->score << endl;
}

int main()
{
	// 结构体作函数参数
	// 将学生传入到一个参数中，打印学生身上的所有信息

	// 创建结构体变量
	student stu = {"张三", 18, 100};
	stu.name = "李四";
	stu.age = 20;
	stu.score = 85;

	// 1、值传递
	printStudent1(stu);
	cout << "1主函数中\t姓名：" << stu.name << "\t年龄：" << stu.age << "\t分数：" << stu.score << endl;

	cout << endl;

	// 2、地址传递
	printStudent2(&stu);
	cout << "2主函数中\t姓名：" << stu.name << "\t年龄：" << stu.age << "\t分数：" << stu.score << endl;

	system("pause");
	return 0;
}