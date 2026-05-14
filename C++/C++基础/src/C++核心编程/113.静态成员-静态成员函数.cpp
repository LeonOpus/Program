#include <iostream> //示例2：静态成员函数
using namespace std;

// 静态成员函数
// 所有对象共享同一个函数
// 静态成员函数只能访问静态成员变量

class Person
{
public:
	// 静态成员函数特点：
	// 1、程序共享一个函数
	// 2、静态成员函数只能访问静态成员变量
	static void func1()
	{ // 静态成员函数
		cout << "static void func1调用！" << endl;
		m_A = 100; // 静态成员函数可以访问静态成员变量，m_A数据共享
		// m_B = 100; //错误，静态成员函数不可以访问非静态成员变量，无法区分到底是哪个对象的m_B属性
	}
	static int m_A; // 静态成员变量
	int m_B;		// 非静态成员变量
private:
	// 静态成员函数也是有访问权限的
	static void func2()
	{
		cout << "static void func2调用！" << endl;
	}
};

int Person::m_A = 10; // 静态成员变量

void test01()
{
	// 静态成员变量两种访问方式

	// 1、通过对象访问
	Person p1;
	p1.func1();

	// 2、通过类名访问
	Person::func1();

	// Person::func2();//私有权限访问不到，类外访问不到私有静态成员函数
}

int main()
{
	test01();
	return 0;
}