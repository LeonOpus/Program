#include <iostream>
#include <string>
using namespace std;

// 立方体类设计
// 1、创建立方体类
// 2、设计属性
// 3、设计行为，获取立方体面积和体积
// 4、分别利用全局函数和成员函数判断两个立方体是否相等

// 创建立方体类
class Cube
{
private:
    // 属性一般设置为私有，长宽高
    int m_L; // 长
    int m_W; // 宽
    int m_H; // 高

public:
    void setL(int L)
    { // 设置长
        m_L = L;
    }
    int getL()
    { // 获取长
        return m_L;
    }

    void setW(int W)
    { // 设置宽
        m_W = W;
    }
    int getW()
    { // 获取宽
        return m_W;
    }

    void setH(int H)
    { // 设置高
        m_H = H;
    }
    int getH()
    { // 获取高
        return m_H;
    }

    int getS()
    { // 行为1：获取立方体面积
        return 2 * (m_L * m_W + m_L * m_H + m_W * m_H);
    }
    int getV()
    { // 行为2：获取立方体体积
        return m_L * m_W * m_H;
    }

    // 利用成员函数判断两个立方体是否相等 isSameByClass()
    bool isSame01(Cube &b)
    { // 只需要传另一个立方体进来与类内的立方体进行比较
        if (m_L == b.getL() && m_W == b.getW() && m_H == b.getH())
            return true;
        else
            return false;
    }
};

// 全局函数
bool isSame02(Cube &a, Cube &b)
{
    if (a.getL() == b.getL() && a.getW() == b.getW() && a.getH() == b.getH())
        return true;
    return false;
}

int main()
{
    // 创建一个立方体对象
    Cube a1;
    a1.setL(10);
    a1.setW(10);
    a1.setH(10);
    cout << "立方体a1的面积为：" << a1.getS() << endl;
    cout << "立方体a1的体积为：" << a1.getV() << endl;

    Cube a2;
    a2.setL(10);
    a2.setW(10);
    a2.setH(12);
    cout << "立方体a1的面积为：" << a2.getS() << endl;
    cout << "立方体a1的体积为：" << a2.getV() << endl;

    // 利用成员函数判断两个立方体是否相等
    bool flag = a2.isSame01(a1);
    if (flag)
        cout << "成员函数判断：立方体a1与立方体a2相等。" << endl;
    else
        cout << "成员函数判断：立方体a1与立方体a2不相等。" << endl;

    // 利用全局函数判断两个立方体是否相等
    bool ret = isSame02(a1, a2);
    if (ret)
        cout << "全局函数判断：立方体a1与立方体a2相等。" << endl;
    else
        cout << "全局函数判断：立方体a1与立方体a2不相等。" << endl;
    return 0;
}