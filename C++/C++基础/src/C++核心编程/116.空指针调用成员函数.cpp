#include <iostream> //空指针访问(调用)成员函数
using namespace std;

class Person
{
public:
    void ShowClassName()
    {
        cout << "This is Person class! 我是Person类！" << endl;
    }
    void ShowPersonAge()
    {
        if (this == NULL)
        {
            return;
        }
        cout << "age = " << m_Age << endl; // this->m_Age
    }

public:
    int m_Age;
};

void test01()
{
    Person *p = NULL;   // 空指针
    p->ShowClassName(); // 空指针，可以调用成员函数

    //(代码报错)报错原因是因为传入的指针是为NULL
    p->ShowPersonAge(); // 但是如果成员函数中用到了this指针，就不可以了
}

int main()
{
    test01();
    return 0;
}