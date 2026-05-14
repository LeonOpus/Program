#include <iostream>
using namespace std;

// 1、值传递：实现两个数字进行交换
void swap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
	cout << "swap01中 a = " << a << endl;
	cout << "swap01中 b = " << b << endl;
}

// 2、地址传递
void swap02(int *p1, int *p2)
{
	int temp = *p1; // 解出内存 解引用
	*p1 = *p2;
	*p2 = temp;
	cout << "swap02中 *p1 = " << *p1 << endl;
	cout << "swap02中 *p2 = " << *p2 << endl;
}

int main() // 指针和函数
{
	int a = 10;
	int b = 20;

	// 1、值传递不会改变实参
	swap01(a, b);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	// 2、地址传递会改变实参
	// 将a、b变量地址传入函数体中，用指针接受地址【如果是地址传递，可以修饰实参】
	swap02(&a, &b);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	return 0;
}