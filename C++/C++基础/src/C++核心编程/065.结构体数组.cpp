#include <iostream>
#include <string>
using namespace std;

//结构体数组
//1、定义结构体
struct student
{
	//成员列表
	string name; //姓名
	int age;	 //年龄
	int score;	 //分数
};

int main()
{
	//2、创建结构体数组
	struct student stuArray[3] =
	{
		{"张三", 18, 88},
		{"李四", 28, 99},
		{"王五", 38, 66}
	};

	//3、给结构体数组中的元素赋值
	stuArray[2].name = "赵六";
	stuArray[2].age = 66;
	stuArray[2].score = 99;

	//4、遍历结构体数组
	for (int i = 0; i < 3; i++)
	{
		cout << "姓名：" << stuArray[i].name
			 << "\t年龄：" << stuArray[i].age
			 << "\t分数：" << stuArray[i].score << endl;
	}

	system("pause");
	return 0;
}