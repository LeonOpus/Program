#include <iostream>
using namespace std;

//冒泡排序函数【参数1：数组首地址；参数2：数组长度】
void bubbleSort(int *arr, int len) //int * arr 也可以写为int arr[]
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1]) //如果j > j + 1的值，交换数字
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//打印数组函数
void printArray(int arr[], int len) //void printArray(int *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		// cout << arr[i] << endl;
		cout << arr[i] << "、";
	}
	cout << endl;
}

int main()
{
	//1、创建一个数组
	int arr[10] = {4, 3, 6, 9, 1, 2, 10, 8, 7, 5};
	//数组长度
	int len = sizeof(arr) / sizeof(int);

	//2、创建一个函数实现冒泡排序
	bubbleSort(arr, len); //传递数组地址arr：数组名就是数组的首地址

	//3、打印排序后的数组
	printArray(arr, len); //传递数组地址arr

	system("pause");

	return 0;
}