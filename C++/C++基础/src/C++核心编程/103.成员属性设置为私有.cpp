#include <iostream>
#include <string>
using namespace std;

// 成员属性设置为私有
// 1、可以自己控制读写权限
// 2、对于写权限，我们可以检测数据的有效性

class Person
{ // 设计类：人
public:
    // 【姓名】
    // 姓名设置可读可写，通过setName方法设置可写，通过getName方法设置可读
    void setName(string name) { m_Name = name; }
    string getName() { return m_Name; }

    // 【年龄】
    // 获取年龄，可读可写，如果想修改（年龄的范围必须是0~150之间）
    int getAge() // 年龄设置只读
    {
        m_Age = 10; // 初始化为0岁
        return m_Age;
    }

    // 【情人】
    // 情人设置为只写
    void setLover(string lover) { m_Lover = lover; }

private:
    string m_Name;  // 可读可写 姓名
    int m_Age;      // 只读 年龄
    string m_Lover; // 只写 情人
};

int main()
{
    Person p;
    // 姓名设置
    p.setName("张三");
    cout << "姓名：" << p.getName() << endl;

    // 年龄只读设置
    cout << "年龄：" << p.getAge() << endl;

    // 情人只写设置
    p.setLover("lover");
    // cout << "情人： " << p.m_Lover << endl; //只写属性，不可以读取
    return 0;
}