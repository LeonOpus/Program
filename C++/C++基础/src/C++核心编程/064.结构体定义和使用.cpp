#include <iostream>
#include <string>
using namespace std;

//1、创建学生数据类型：学生包括(姓名、年龄、分数)
//自定义数据类型，一些数据类型集合组成的一个类型(其实就是内置数据类型的集合)。
//语法：struct 类型名称 { 成员列表 }

//结构体定义
struct student //结构体名称-见名知意
{
	//成员列表---学生属性
	string name; //姓名
	int age;	 //年龄
	int score;	 //分数
} stu3;	//结构体变量创建方式3

//2、通过学生类型创建具体学生（共有3种方式）

//2.1、struct student s1; // s1就是变量名
//2.2、struct student s2 = {...}; // 创建变量的同时赋初值
//2.3、在定义结构体时顺便创建结构体变量

int main()
{
	//【结构体变量创建方式1】2.1、struct student s1;
	struct student stu1; //创建结构体时，struct关键字可以省略
	//给stu1属性赋值，通过“.”访问结构体变量中的属性
	stu1.name = "张三";
	stu1.age = 18;
	stu1.score = 100;
	//方式1打印输出
	cout << "姓名：" << stu1.name << " 年龄：" << stu1.age << " 分数：" << stu1.score << endl;

	//【结构体变量创建方式2】2.2、struct student s2 = {...};
	struct student stu2 = {"李四", 19, 60};
	//方式2打印输出
	cout << "姓名：" << stu2.name << " 年龄：" << stu2.age << " 分数：" << stu2.score << endl;

	//【结构体变量创建方式3】在定义结构体时顺便创建结构体变量，不建议使用
	stu3.name = "王五";
	stu3.age = 18;
	stu3.score = 80;
	//方式3打印输出
	cout << "姓名：" << stu3.name << " 年龄：" << stu3.age << " 分数：" << stu3.score << endl;

	system("pause");
	return 0;
}