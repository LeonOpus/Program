#include <iostream>
#include <string>
#include <list>
using namespace std;

// list容器-排序案例-实现自定义数据类型的排序
// 按照年龄进行升序排序，如果年龄相同按照身高进行降序排序

class Person
{
public:
	Person(string name, int age, int height)
	{
		this->m_Name = name;
		this->m_Age = age;
		this->m_Height = height;
	}

public:
	string m_Name; // 姓名
	int m_Age;	   // 年龄
	int m_Height;  // 身高
};

// 自定义比较函数
bool comparePerson(Person &p1, Person &p2)
{
	// 按照年龄进行升序
	if (p1.m_Age == p2.m_Age)
	{
		// 年龄相同按照身高进行降序
		return p1.m_Height > p2.m_Height;
	}
	else
	{
		return p1.m_Age < p2.m_Age;
	}
}

void test01()
{
	list<Person> L; // 创建容器

	// 准备数据
	Person p1("张三", 35, 175);
	Person p2("李四", 45, 180);
	Person p3("王五", 40, 170);
	Person p4("赵六", 25, 190);
	Person p5("陈七", 35, 160);
	Person p6("杨八", 35, 200);

	// 添加数据
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);
	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名：" << (*it).m_Name << " 年龄：" << it->m_Age << " 身高：" << it->m_Height << endl;
	}

	// 排序
	cout << "---------------------------------" << endl;
	cout << "排序后" << endl;
	L.sort(comparePerson); // 排序
	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名：" << (*it).m_Name << " 年龄：" << it->m_Age << " 身高：" << it->m_Height << endl;
	}
}

int main()
{
	test01();
	return 0;
}