#include <iostream> //示例1：设计一个圆类，求圆的周长。
using namespace std;

const double PI = 3.14; // 圆周率

// 封装的意义：将属性和行为作为一个整体，用来表现生活中的事物。

// 封装设计一个圆类，求圆的周长。圆求周长的公式：2* PI*半径
// class代表设计一个类，类后面跟着的就是类名称
class Circle
{
public: // 访问权限：公共的权限
    // 属性
    int m_r; // 半径

    // 行为
    double calculateZC()
    {                        // 获取到圆的周长
        return 2 * PI * m_r; // 2 * pi  * r，获取圆的周长
    }
};

int main()
{
    // 通过圆类，创建具体的圆(对象)，实例化(通过一个类创建一个对象的过程)
    Circle c1;   // c1就是一个具体的圆
    c1.m_r = 10; // 给圆对象的半径属性进行赋值操作

    // 2 * pi * 10 = = 62.8
    cout << "圆的周长为：" << c1.calculateZC() << endl; // 圆的周长为：62.8

    system("pause");
    return 0;
}