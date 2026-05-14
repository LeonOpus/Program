#include <iostream>
using namespace std;

// 抽象不同的零件类
class CPU
{ // 抽象CPU类
public:
    virtual void calculate() = 0; // 抽象的计算函数
};

class VideoCard
{ // 抽象显卡类
public:
    virtual void display() = 0; // 抽象的显示函数
};

class Memory
{ // 抽象内存条类
public:
    virtual void storage() = 0; // 抽象的存储函数
};

class Computer
{ // 电脑类
public:
    Computer(CPU *cpu, VideoCard *vc, Memory *mem)
    {
        m_cpu = cpu;
        m_vc = vc;
        m_mem = mem;
    }
    void work()
    { // 提供工作的函数
        // 让零件工作起来，调用接口
        m_cpu->calculate();
        m_vc->display();
        m_mem->storage();
    }
    ~Computer()
    { // 提供析构函数，释放3个电脑零件
        if (m_cpu != NULL)
        { // 释放CPU零件
            delete m_cpu;
            m_cpu = NULL;
        }
        if (m_vc != NULL)
        { // 释放显卡零件
            delete m_vc;
            m_vc = NULL;
        }
        if (m_mem != NULL)
        { // 释放内存条零件
            delete m_mem;
            m_mem = NULL;
        }
    }

private:
    CPU *m_cpu;      // CPU的零件指针
    VideoCard *m_vc; // 显卡零件指针
    Memory *m_mem;   // 内存条零件指针
};

// 具体厂商
// Intel厂商
class IntelCPU : public CPU
{
public:
    virtual void calculate()
    {
        cout << "Intel的CPU开始计算了！" << endl;
    }
};

class IntelVideoCard : public VideoCard
{
public:
    virtual void display()
    {
        cout << "Intel的显卡开始显示了！" << endl;
    }
};

class IntelMemory : public Memory
{
public:
    virtual void storage()
    {
        cout << "Intel的内存条开始存储了！" << endl;
    }
};

// Lenovo厂商
class LenovoCPU : public CPU
{
public:
    virtual void calculate()
    {
        cout << "Lenovo的CPU开始计算了！" << endl;
    }
};

class LenovoVideoCard : public VideoCard
{
public:
    virtual void display()
    {
        cout << "Lenovo的显卡开始显示了！" << endl;
    }
};

class LenovoMemory : public Memory
{
public:
    virtual void storage()
    {
        cout << "Lenovo的内存条开始存储了！" << endl;
    }
};

void test01()
{
    // 第一台电脑零件
    CPU *intelCpu = new IntelCPU;
    VideoCard *intelCard = new IntelVideoCard;
    Memory *intelMem = new IntelMemory;

    cout << "第一台电脑开始工作：" << endl;
    // 创建第一台电脑
    Computer *computer1 = new Computer(intelCpu, intelCard, intelMem);
    computer1->work();
    delete computer1;

    cout << "-----------------------" << endl;
    cout << "第二台电脑开始工作：" << endl;
    // 第二台电脑组装
    Computer *computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);
    ;
    computer2->work();
    delete computer2;

    cout << "-----------------------" << endl;
    cout << "第三台电脑开始工作：" << endl;
    // 第三台电脑组装
    Computer *computer3 = new Computer(new LenovoCPU, new IntelVideoCard, new LenovoMemory);
    ;
    computer3->work();
    delete computer3;
}

int main()
{
    test01();
    return 0;
}