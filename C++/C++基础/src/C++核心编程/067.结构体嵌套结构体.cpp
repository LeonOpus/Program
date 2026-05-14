#include <iostream>
#include <string>
using namespace std;

// 结构体嵌套结构体

// 定义学生结构体
struct student
{
	// 成员列表
	string name; // 姓名
	int age;	 // 年龄
	int score;	 // 分数
};

// 定义教师结构体
struct teacher
{
	// 成员列表
	int id;				// 教师编号
	string name;		// 教师姓名
	int age;			// 教师年龄
	struct student stu; // 教师辅导的学生 子结构体
};

int main()
{
	// 创建教师结构体变量
	struct teacher t1;
	t1.id = 333;
	t1.name = "老王";
	t1.age = 50;

	t1.stu.name = "张三";
	t1.stu.age = 18;
	t1.stu.score = 99;

	cout << "教师编号：" << t1.id
		 << "\t教师姓名：" << t1.name
		 << "\t教师年龄：" << t1.age
		 << "\t教师辅导的学生姓名：" << t1.stu.name
		 << endl;

	cout << "学生姓名：" << t1.stu.name
		 << "\t学生年龄：" << t1.stu.age
		 << "\t学生考试分数：" << t1.stu.score
		 << endl;

	system("pause");
	return 0;
}