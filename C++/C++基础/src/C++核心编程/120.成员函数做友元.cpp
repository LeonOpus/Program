#include <iostream>
#include <string>
using namespace std;

class Building;

class goodGay
{
public:
    goodGay();     // 构造函数
    void visit();  // 只让visit函数作为Building的好朋友，可以访问Building中私有内容
    void visit2(); // 让visit2函数不可以访问Building中私有成员
private:
    Building *building;
};

class Building
{
    // 告诉编译器：goodGay类中的visit成员函数是Building好朋友，可以访问私有内容
    // 告诉编译器GoodGay类下的visit成员函数作为本类的好朋友，可以访问私有成员
    friend void goodGay::visit();

public:
    Building();

public:
    string m_SittingRoom; // 客厅
private:
    string m_BedRoom; // 卧室
};

Building::Building()
{ // 类外实现成员函数
    this->m_SittingRoom = "客厅";
    this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{                            // goodGay构造函数的实现
    building = new Building; // 在堆区创建一个Building对象并用指针维护
}

void goodGay::visit()
{
    cout << "好基友正在访问" << building->m_SittingRoom << endl;
    cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void goodGay::visit2()
{
    cout << "好基友正在访问" << building->m_SittingRoom << endl;
    // cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
    goodGay gg;
    gg.visit();
    gg.visit2();
}

int main()
{
    test01();
    return 0;
}