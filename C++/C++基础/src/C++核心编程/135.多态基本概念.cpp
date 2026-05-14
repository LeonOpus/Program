#include <iostream>
using namespace std;

class Animal
{ // 动物类
public:
    // 函数前面加上virtual关键字变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
    virtual void speak()
    { // Speak函数就是虚函数
        cout << "动物在说话..." << endl;
    }
};

class Cat : public Animal
{ // 猫类
public:
    // 重写：函数返回值类型、函数名、参数列表，完全相同
    // 重载：函数名相同，参数列表不同
    void speak()
    {
        cout << "小猫在说话..." << endl;
    }
};

class Dog : public Animal
{ // 狗类
public:
    void speak()
    {
        cout << "小狗在说话..." << endl;
    }
};
// 我们希望传入什么对象，那么就调用什么对象的函数
// 如果函数地址在编译阶段就能确定，那么静态联编
// 如果函数地址在运行阶段才能确定，就是动态联编

// 执行说话的函数
// 地址早绑定，在编译阶段确定函数地址
// 如果想执行让猫说话，那么这个函数地址就不能提前绑定，需要在运行阶段进行绑定，地址晚绑定
void DoSpeak(Animal &animal)
{ // Animal & animal = cat;
    animal.speak();
}

// 动态多态满足条件：
// 1、有继承关系；
// 2、子类重写父类中的虚函数
// 动态多态使用：父类指针或引用指向子类对象

void test01()
{
    Cat cat;
    DoSpeak(cat); // 小猫在说话...
    Dog dog;
    DoSpeak(dog); // 小狗在说话...
}

void test02()
{
    cout << "sizeof Animal = " << sizeof(Animal) << endl;
}

int main()
{
    test01();
    test02();
    system("pause");
    return 0;
}