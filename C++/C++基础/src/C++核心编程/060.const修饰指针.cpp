#include <iostream>
using namespace std;

int main()
{
	int a = 10;
	int b = 10;
	// int *p0 = &a; //普通写法

	// 1、常量指针(记法：const在前 先常量 后指针)
	// const修饰的是指针，指针的指向可以更改，指针指向的值不可以更改(可以理解为const 修饰的是解引用 int*，所以指针指向的值不可以更改)
	const int *p1 = &a;
	p1 = &b; // 正确
	// *p1 = 20; //错误

	// 2、指针常量(记法：int* 在前 先指针 后常量)
	// const修饰的是常量，指针的指向不可以更改，指针指向的值可以更改(可以理解为const修饰的是指针本身，所以指针指向的值不可以修改)
	int *const p2 = &a;
	*p2 = 100; // 正确
	// p2 = &b; //错误，指针常量 指针的指向不可以更改

	// 3、const既修饰指针又修饰常量
	const int *const p3 = &a;
	// 指针的指向和指针指向的值都不可以改
	//*p3 = 100; //错误
	// p3 = &b; //错误
	return 0;
}