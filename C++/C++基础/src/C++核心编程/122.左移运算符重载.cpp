#include <iostream>
using namespace std;

class Person
{
	// 利用成员函数重载左移运算符
	// p.operator<<(cout)，简化版本：p << cout
	// 不会利用成员函数重载<<运算符，因为无法实现cout在左侧
	// ostreamb标准输出流对象
	friend ostream &operator<<(ostream &out, Person &p);

public:
	Person();
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
	// 成员函数 实现不了  p << cout 不是我们想要的效果
	// void operator<<(Person& p){
	// }
private: // private public
	int m_A;
	int m_B;
};

// 只能利用全局函数重载左移运算符
// 全局函数实现左移重载，ostream对象只能有一个
// 本质operator<<(cout,p)，简化cout<<p
ostream &operator<<(ostream &out, Person &p)
{
	out << "p.m_A：" << p.m_A << "，p.m_B：" << p.m_B << endl;
	return out;
}

void test()
{
	Person p;
	// p.m_A = 1;
	// p.m_B = 2;
	cout << p;

	Person p1(10, 20);
	cout << p1 << "hello world !" << endl; // 链式编程
}

int main()
{
	test();
	return 0;
}