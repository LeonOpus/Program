#include <iostream> //示例3：三种访问权限
using namespace std;

// 三种访问权限
// 1、公共权限 public    成员 类内可以访问 类外可以访问
// 2、保护权限 protected 成员 类内可以访问 类外不可以访问 儿子可以访问父亲中的保护内容
// 3、私有权限 private   成员 类内可以访问 类外不可以访问 儿子不可以访问父亲的私有内容

//保护权限下 父亲有辆车，儿子可以访问使用父亲保护的车，和父亲说一下就行了
//私有权限下 父亲有银行卡，儿子不可以访问父亲的私有银行卡密码

class Person
{
    // 姓名：公共权限
public:
    string m_Name;

    // 汽车：保护权限
protected:
    string m_Car;

    // 银行卡密码：私有权限
private:
    int m_Password;

public:
    void func()
    {
        m_Name = "张三";
        m_Car = "汽车";
        m_Password = 123456;
    }
};

int main()
{
    Person p; // 实例化具体对象
    p.m_Name = "李四";
    // p.m_Car = "奔驰";   //保护权限内容，类外访问不到
    // p.m_Password = 123; //私有权限内容，类外访问不到
    p.func();
    return 0;
}