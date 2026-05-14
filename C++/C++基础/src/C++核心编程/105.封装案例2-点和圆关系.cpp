#include <iostream> //练习案例2：点和圆的关系案例
#include <string>
using namespace std;

class Point
{ // 一个点类（Point）
private:
    int p_x;
    int p_y;

public:
    // 设置x坐标
    void setX(int x)
    {
        p_x = x;
    }
    // 获取x坐标
    int getX()
    {
        return p_x;
    }

    // 设置y坐标
    void setY(int y)
    {
        p_y = y;
    }
    // 获取y坐标
    int getY()
    {
        return p_y;
    }
};

class Circle
{ // 设计一个圆类Circle
public:
    // 设置半径R
    void setR(int r)
    {
        R = r;
    }
    // 获取半径R
    int getR()
    {
        return R;
    }

    // 设置圆心
    void setCenter(Point center)
    {
        c_center = center;
    }
    // 获取圆心
    Point getCenter()
    { // c_center是Piont类的数据
        return c_center;
    }

private:
    int R;
    // 在类中可以让另一个类作为本类中的成员--与结构体相似
    Point c_center;
};

// 判断点和圆的关系
void isInCircle(Circle &c, Point &p)
{
    // 计算两点之间距离的平方
    int pDistance = (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
                    (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
    // 计算半径的平方
    int rDistance = c.getR() * c.getR();
    // 判断关系
    if (pDistance == rDistance)
    {
        cout << "点在圆上。" << endl;
    }
    else if (pDistance > rDistance)
        cout << "点在圆外。" << endl;
    else if (pDistance < rDistance)
        cout << "点在圆内。" << endl;
    // if ((p.getX() - c.getCenter().getX()) * (p.getX() - c.getCenter().getX()) + (p.getY() - c.getCenter().getY()) * (p.getY() - c.getCenter().getY()) == c.getR() * c.getR())
    //     cout << "点在圆上。" << endl;
    // else if ((p.getX() - c.getCenter().getX()) * (p.getX() - c.getCenter().getX()) + (p.getY() - c.getCenter().getY()) * (p.getY() - c.getCenter().getY()) > c.getR() * c.getR())
    //     cout << "点在圆外。" << endl;
    // else
    //     cout << "点在圆内。" << endl;
}

int main()
{
    // 创建并设置点P1(10,9)
    Point P1;
    P1.setX(10);
    P1.setY(9);

    // 创建并设置点P2-圆心(10,0)
    Point P2;
    P2.setX(10);
    P2.setY(0);

    // 设置圆C1
    Circle C1;
    C1.setR(10);
    C1.setCenter(P2); // 圆心(10,0)

    isInCircle(C1, P1); // 点在圆内。

    return 0;
}