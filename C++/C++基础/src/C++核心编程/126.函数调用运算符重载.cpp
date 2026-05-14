#include <iostream>
#include <string>
using namespace std;

class MyPrint
{ // 打印输出类
public:
	void operator()(string text)
	{ // 重载函数调用运算符
		cout << text << endl;
	}
};

void MyPrintFunc(string str)
{ // 普通函数
	cout << str << endl;
}

void test01()
{
	MyPrintFunc("abc");	   // 普通函数调用
	MyPrint myFunc;		   // 由于使用起来非常类似于函数调用，因此称为仿函数
	myFunc("hello world"); // 重载的()操作符，也称为仿函数。仿函数非常灵活，没有固定的写法
}

class MyAdd
{ // 加法类
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

void test02()
{
	MyAdd add;
	int ret = add(10, 10);
	cout << "ret = " << ret << endl; // ret = 20
	// 匿名对象调用，当前函数执行完毕后匿名对象会被立即释放。
	cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl; // MyAdd()(100,100) = 200
}

int main()
{
	test01();
	test02();
	return 0;
}