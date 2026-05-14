#include <iostream>
using namespace std;

class Base
{
public:
	static void func()
	{
		cout << "Base - static void func()" << endl;
	}
	static void func(int a)
	{
		cout << "Base - static void func(int a)" << endl;
	}
	static int m_A;
};
int Base::m_A = 100; // 静态变量，类内声明、类外初始化

class Son : public Base
{
public:
	static void func()
	{
		cout << "Son - static void func()" << endl;
	}
	static int m_A;
};
int Son::m_A = 200;

void test01()
{ // 同名静态成员属性
	// 1、通过对象访问
	cout << "通过对象访问：" << endl;
	Son s;
	cout << "Son下，m_A = " << s.m_A << endl;
	cout << "Base下，m_A = " << s.Base::m_A << endl;
	// 2、通过类名访问
	cout << "通过类名访问：" << endl;
	cout << "Son下，m_A = " << Son::m_A << endl;
	// 第一个::代表通过类名方式访问，第二个::代表访问父类作用域下的m_A
	cout << "Base下，m_A = " << Son::Base::m_A << endl;
}

void test02()
{ // 同名静态成员函数
	// 1、通过对象访问
	cout << "通过对象访问：" << endl;
	Son s;
	s.func();
	s.Base::func();
	// 2、通过类名访问
	cout << "通过类名访问：" << endl;
	Son::func();
	Son::Base::func();
	// 出现同名，子类会隐藏掉父类中所有同名成员函数，需要加作用域访问
	// 子类出现和父类同名静态成员函数，会隐藏掉父类中的所有同名成员函数
	// 如果想访问父类中被隐藏的同名成员，需要加作用域
	Son::Base::func(100);
}

int main()
{
	// test01();
	test02();
	system("pause");
	return 0;
}