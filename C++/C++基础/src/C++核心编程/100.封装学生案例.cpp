#include <iostream> //示例2：设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号。
#include <string>
using namespace std;

class Student
{       // 学生类
public: // 公共权限
    // 类中的属性和行为，我们统一称为“成员”。
    // “属性”别名：成员属性、成员变量
    // “行为”别名：成员函数、成员方法

    // 属性
    string m_name; // 姓名
    int m_id;      // 学号

    // 行为
    void setName(string name)
    { // 给姓名赋值
        m_name = name;
    }
    void setID(int id)
    { // 给学号赋值
        m_id = id;
    }
    void showStudent()
    { // 显示姓名与学号
        cout << "name：" << m_name << " ID:" << m_id << endl;
    }
    // public:
    //     string m_name;
    //     int m_id;
};

int main()
{
    Student s1; // 创建一个具体学生，实例化对象
    // 给s1对象进行属性赋值操作
    s1.m_name = "张三";
    s1.setName("zs");
    s1.m_id = 1;
    s1.showStudent();

    Student stu;
    stu.setName("李四");
    stu.setID(250);
    stu.showStudent();
    return 0;
}