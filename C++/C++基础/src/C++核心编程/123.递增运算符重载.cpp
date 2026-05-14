#include <iostream>
using namespace std;

class MyInteger
{ // 自定义整型
	friend ostream &operator<<(ostream &out, MyInteger myint);

public:
	MyInteger()
	{
		m_Num = 0;
	}
	MyInteger &operator++()
	{ // 重载前置++运算符，前置++
		// 返回&引用是为了一直对一个数据进行递增操作
		m_Num++;	  // 先进行++运算
		return *this; // 再将自身返回，*返回自身
	}
	MyInteger operator++(int)
	{ // 重载后置++运算符，后置++；int代表占位参数，可以用于区分前置和后置递增
		// 先记录当时的结果，临时变量-局部对象，当前函数执行完之后对象就被释放了，不可返回地址；所以前置返回引用、后置返回值
		MyInteger temp = *this; // 记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
		m_Num++;				// 后递增操作
		return temp;			// 最后将记录结果返回
	}

private:
	int m_Num;
};

// 重载<<运算符
ostream &operator<<(ostream &out, MyInteger myInt)
{
	out << myInt.m_Num;
	return out;
}

// 前置++：先++再返回
void test01()
{
	MyInteger myInt;
	cout << ++myInt << endl;
	cout << myInt << endl;
	cout << ++(++myInt) << endl;
}

// 后置++：先返回再++
void test02()
{
	MyInteger myInt;
	cout << myInt++ << endl;
	cout << myInt << endl;
}

int main()
{
	test01();
	// test02();
	int a = 0;
	cout << ++(++a) << endl; // 2
	cout << a << endl;		 // 2
	return 0;
}