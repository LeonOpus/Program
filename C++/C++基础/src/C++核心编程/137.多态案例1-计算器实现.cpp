#include <iostream> //分别利用普通写法和多态技术实现计算器
#include <string>
using namespace std;

// 普通实现
class Calculator
{
public:
    int getResult(string oper)
    {
        if (oper == "+")
        {
            return m_Num1 + m_Num2;
        }
        else if (oper == "-")
        {
            return m_Num1 - m_Num2;
        }
        else if (oper == "*")
        {
            return m_Num1 * m_Num2;
        }
        // 如果要提供新的运算、想拓展新的功能，需要修改源码
        // 在真实开发中提倡开闭原则
        // 开闭原则：对扩展进行开放，对修改进行关闭
    }

public:
    int m_Num1;
    int m_Num2;
};

void test01()
{                  // 普通实现测试
    Calculator c;  // 创建计算器对象
    c.m_Num1 = 10; // 操作数1
    c.m_Num2 = 20; // 操作数2
    cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.getResult("+") << endl;
    cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.getResult("-") << endl;
    cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.getResult("*") << endl;
}

// 多态实现
// 抽象计算器类
// 多态优点好处：1.代码组织结构清晰，2.可读性强，3.利于前期和后期的扩展以及维护。
class AbstractCalculator // 实现计算机抽象类
{
public:
    virtual int getResult()
    {
        return 0;
    }
    int m_Num1;
    int m_Num2;
};

class AddCalculator : public AbstractCalculator
{ // 加法计算器类
public:
    int getResult()
    {
        return m_Num1 + m_Num2;
    }
};

class SubCalculator : public AbstractCalculator
{ // 减法计算器类
public:
    int getResult()
    {
        return m_Num1 - m_Num2;
    }
};

class MulCalculator : public AbstractCalculator
{ // 乘法计算器类
public:
    int getResult()
    {
        return m_Num1 * m_Num2;
    }
};

void test02()
{ // 多态使用条件：父类指针或者引用指向子装对象
    // 创建加法计算器
    AbstractCalculator *abc = new AddCalculator;
    abc->m_Num1 = 100;
    abc->m_Num2 = 200;
    cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;
    delete abc; // 用完了记得销毁，堆区数据

    // 创建减法计算器
    abc = new SubCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;
    cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->getResult() << endl;
    delete abc;

    // 创建乘法计算器
    abc = new MulCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;
    cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->getResult() << endl;
    delete abc;
}

int main()
{
    // test01();
    test02();
    system("pause");
    return 0;
}