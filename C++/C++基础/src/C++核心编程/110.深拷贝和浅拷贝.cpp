#include <iostream>
using namespace std;

class Person
{
public:
    // 无参（默认）构造函数
    Person()
    {
        cout << "Person的无参(默认)构造函数调用!" << endl;
    }
    // 有参构造函数
    Person(int age, int height)
    {
        cout << "Person的有参构造函数调用!" << endl;
        m_age = age;
        m_height = new int(height); // 数据放在堆区，堆区数据需要手动开辟与手动释放
    }
    // 拷贝构造函数，自己实现拷贝构造函数解决浅拷贝带来的问题
    Person(const Person &p)
    {
        cout << "Person的拷贝构造函数调用!" << endl;
        // 如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
        m_age = p.m_age;
        // m_height = p.m_height;//编译器默认实现就是这行代码
        m_height = new int(*p.m_height); // 深拷贝操作，解决浅拷贝重复释放堆区问题
    }
    // 析构函数
    ~Person()
    { 
        // 析构代码，将堆区开辟数据做释放操作
        if (m_height != nullptr)
        {
            delete m_height;
            m_height = nullptr;
        }
        cout << "Person的析构函数调用!" << endl;
    }

public:
    int m_age;     // 年龄
    int *m_height; // 指针指向身高
};

void test01()
{
    Person p1(18, 181);
    cout << "p1的年龄： " << p1.m_age << "，身高：" << *p1.m_height << endl;
    Person p2(p1);
    cout << "p2的年龄： " << p2.m_age << "，身高：" << *p2.m_height << endl;
}

int main()
{
    test01();
    return 0;
}