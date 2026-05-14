#include <iostream>
using namespace std;

int main() // 指针所占内存空间
{
	int a = 10;

	// int *p;
	// p = &a; //指针指向数据a的数据地址
	int *p = &a; // 建立关系

	// 在32位操作系统下，指针是占4个字节空间大小（不管是什么数据类型）
	// 在64位操作系统下，指针是占4个字节空间大小（不管是什么数据类型）
	cout << *p << endl;										   // 10 * 解引用
	cout << "sizeof(p) = " << sizeof(p) << endl;			   // 8 查看变量（数据类型）占用的内存空间
	cout << "sizeof(int *) = " << sizeof(int *) << endl;	   // 8
	cout << "sizeof(float *) = " << sizeof(float *) << endl;   // 8
	cout << "sizeof(double *) = " << sizeof(double *) << endl; // 8
	cout << "sizeof(char *) = " << sizeof(char *) << endl;	   // 8
	return 0;
}