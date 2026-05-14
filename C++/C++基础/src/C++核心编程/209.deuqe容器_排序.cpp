 #include <iostream>
#include <deque>
#include <algorithm>//标准算法头文件
using namespace std;

void printDeque(const deque<int> &d) {
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	//deque容器排序
	deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_front(100);
	d.push_front(200);
	d.push_front(300);
	printDeque(d);//300 200 100 10 20 30
	//排序-默认从小到大排序
	//支持随机访问的迭代器，才能使用sort算法直接对其排序
	//vector容器也可以使用sort排序
	sort(d.begin(), d.end());
	cout << "排序后" << endl;
	printDeque(d);
}

int main() {
	test01();
	return 0;
}