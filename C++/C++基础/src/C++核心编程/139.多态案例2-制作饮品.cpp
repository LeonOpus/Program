#include <iostream>
using namespace std;

class AbstractDrinking
{
    // 抽象制作饮品
public:
    // 烧水
    virtual void Boil() = 0;
    // 冲泡
    virtual void Brew() = 0;
    // 倒入杯中
    virtual void PourInCup() = 0;
    // 加入辅料
    virtual void PutSomething() = 0;
    // 规定流程
    void MakeDrink()
    {
        Boil();
        Brew();
        PourInCup();
        PutSomething();
    }
};

class Coffee : public AbstractDrinking
{ // 制作咖啡
public:
    // 烧水
    virtual void Boil()
    {
        cout << "煮农夫山泉!" << endl;
    }
    // 冲泡
    virtual void Brew()
    {
        cout << "冲泡咖啡!" << endl;
    }
    // 倒入杯中
    virtual void PourInCup()
    {
        cout << "将咖啡倒入杯中!" << endl;
    }
    // 加入辅料
    virtual void PutSomething()
    {
        cout << "加入牛奶!" << endl;
    }
};

class Tea : public AbstractDrinking
{ // 制作茶水
public:
    // 烧水
    virtual void Boil()
    {
        cout << "煮自来水!" << endl;
    }
    // 冲泡
    virtual void Brew()
    {
        cout << "冲泡茶叶!" << endl;
    }
    // 倒入杯中
    virtual void PourInCup()
    {
        cout << "将茶水倒入杯中!" << endl;
    }
    // 加入辅料
    virtual void PutSomething()
    {
        cout << "加入枸杞!" << endl;
    }
};

void DoWork(AbstractDrinking *drink)
{ // 业务函数-制作饮品函数
    // AbstractDrinking *abs = new Coffee();
    drink->MakeDrink();
    delete drink; // 释放堆区数据
} 

void test01()
{
    DoWork(new Coffee); // 制作咖啡
    cout << "--------------" << endl;
    DoWork(new Tea); // 制作茶水
}

int main()
{
    test01();
    return 0;
}