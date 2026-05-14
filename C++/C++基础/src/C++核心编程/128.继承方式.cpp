#include <iostream>
using namespace std;

class Base1
{ // 公共继承
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};
class Son1 : public Base1
{
public:
    void func()
    {
        m_A; // 父类中的公共权限成员到子类中依然是公共权限，可访问public权限
        m_B; // 父类中的保护权限成员到子类中依然是保护权限，可访问protected权限
        // m_C;//父类中的私有权限成员子类访问不到，子类不可访问
    }
};
void myClass()
{
    Son1 s1;
    s1.m_A = 100; // 其他类只能访问到公共权限
    // s1.m_B = 100;//到Son1中，m_B是保护权限，类外访问不到
}

class Base2
{ // 保护继承
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};
class Son2 : protected Base2
{
public:
    void func()
    {
        m_A; // 可访问protected权限。父类中公共成员，到子类中变为保护权限
        m_B; // 可访问protected权限。父类中保护成员，到子类中变为保护权限
        // m_C;//父类中私有成员子类访问不到，不可访问
    }
};
void myClass2()
{
    Son2 s;
    // s.m_A = 1000;//在Son2中m_A变为保护权限，因此类外访问不到
    // s.m_B = 1000;//在Son2中，m_B保护权限，不可以访问
}

class Base3
{ // 私有继承
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};
class Son3 : private Base3
{
public:
    void func()
    {
        m_A; // 可访问 private权限 父类中公共成员到子类中变为私有成员
        m_B; // 可访问 private权限 父类中保护成员到子类中变为私有成员
        // m_C; //不可访问 父类中私有成员，子类访问不到
    }
};
class GrandSon3 : public Son3
{
public:
    void func()
    {
        // Son3是私有继承，所以继承Son3的属性在GrandSon3中都无法访问到
        // m_A;//到了Son3中，m_A变为私有，即使是儿子，也是访问不到
        // m_B;//到了Son3中，m_B变为私有，即使是儿子，也是访问不到
        // m_C;
    }
};
void myClass3()
{
    Son3 s1;
    // s.m_A = 1000;//在Son3中，m_A变为保护权限，因此类外访问不到
    // s.m_B = 1000;//在Son3中，m_B变为保护权限，不可以访问
}

int main()
{
    return 0;
}