#include <iostream>
using namespace std;

class Person
{
public:
	Person() {};
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
	// 1、成员函数实现+号运算符重载
	Person operator+(const Person &p)
	{
		Person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}

public:
	int m_A;
	int m_B;
};

// 2、全局函数实现+号运算符重载
Person operator+(const Person &p1, const Person &p2)
{
	Person temp(0, 0);
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}

// 运算符重载，可以发生函数重载
Person operator+(const Person &p2, int val)
{ // 函数重载版本
	Person temp;
	temp.m_A = p2.m_A + val;
	temp.m_B = p2.m_B + val;
	return temp;
}

void test()
{
	// Person p;
	// p.m_A = 10;
	// p.m_B = 10;
	Person p1(10, 10);
	Person p2(20, 20);

	// 成员函数方式
	Person p3 = p2 + p1; // 相当于p2.operaor+(p1)，成员函数重载本质调用
	cout << "p3.mA：" << p3.m_A << "，p3.mB：" << p3.m_B << endl;

	// 全局函数方式，Person+int
	Person p4 = p3 + 10; // 相当于operator+(p3,10)，全局函数重载本质调用
	cout << "p4.mA：" << p4.m_A << "，p4.mB：" << p4.m_B << endl;
}

int main()
{
	test();
	return 0;
}