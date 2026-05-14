#include <iostream>//deque构造函数
#include <deque>
using namespace std;

void printDeque(const deque<int> &d) {
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
        //*it = 100;//const迭代器不允许修改容器中的数据
        cout << *it << " ";
    }
    cout << endl;
}

//测试deque的构造函数
void test01() {
    //默认构造
    deque<int> d1;
    for (int i = 0; i < 10; i++) {
        d1.push_back(i);
    }
    printDeque(d1);//0 1 2 3 4 5 6 7 8 9

    //区间构造
    deque<int> d2(d1.begin(), d1.end());
    printDeque(d2);//0 1 2 3 4 5 6 7 8 9

    //n个elem构造
    deque<int> d3(10, 100);
    printDeque(d3);//100 100 100 100 100 100 100 100 100 100

    //拷贝构造
    deque<int> d4(d3);
    printDeque(d4);//100 100 100 100 100 100 100 100 100 100
}

int main() {
    test01();
    system("pause");
    return 0;
}