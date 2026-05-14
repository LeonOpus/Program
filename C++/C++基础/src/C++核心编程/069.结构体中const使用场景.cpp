#include <iostream>
#include <string>
using namespace std;

//学生结构体定义
struct student
{
	//成员列表
	string name; //姓名
	int age;	 //年龄
	int score;	 //分数
};

/*
 * 值传递
 * stu.age = 150;//mian中的stu变量不会改变
 * 会将实参中的数据拷贝一份，放在形参s上
 * 无论形参如何改变，都不会影响实参
 * 1、实参有很多属性，每个属性都拷贝一份，拷贝的数据量很大
 * 2、假设一个学校有成千上万个人，每个人都调用printStudent函数，拷贝成千上万份数据，
 *    这样数据量就会非常大，占用内存空间大
 */
void printStudent1(student stu) // (struct student stu) 省略struct
{
	stu.age = 150; //mian中的stu变量不会改变
	cout << "姓名：" << stu.name << "\t年龄：" << stu.age << "\t分数：" << stu.score << endl;
}

// void printStudent3(const student stu) // (struct student stu) 省略struct
// {
// 	stu.age = 150; //mian中的stu变量不会改变
// 	cout << "姓名：" << stu.name << "\t年龄：" << stu.age << "\t分数：" << stu.score << endl;
// }

//将函数中的形参改为指针，可以减少内存空间的使用，而且不会复制新的副本出来（值传递会复制整个结构体元素）
//const使用场景
void printStudent2(const student *stu) //加const防止函数体中的误操作 指针*stu节省空间，一个指针占4个字节内存
{
	//stu->age = 100; //操作失败,因为加了const修饰,常量指针无法修改指针指向的值,只能读不能写。防止age的值会被修改
	//加入const之后，一旦有修改的操作就会报错，可以防止我们的误操作（加“const”防止误操作）
	cout << "姓名：" << stu->name << "\t年龄：" << stu->age << "\t分数：" << stu->score << endl;
}

int main()
{
	//创建结构体变量
	student stu = {"张三", 18, 100};

	printStudent1(stu); //值传递

	//通过函数打印结构体变量信息
	printStudent2(&stu); //传入地址，在函数中指针接收地址

	cout << "main()中 张三的年龄为：" << stu.age << endl;

	system("pause");
	return 0;
}