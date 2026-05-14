#include <iostream> //类模板与继承
using namespace std;

template <class T>
class Base
{
    T m;
};

// class Son:public Base {};//错误，c++编译需要给子类分配内存，必须知道父类中T的类型才可以向下继承
// 错误，必须要知道父类中的T类型，才能继承给子类

class Son : public Base<int>
{
}; // 必须指定一个类型

void test01()
{
    Son s;
}

// 类模板继承类模板，可以用T2指定父类中的T类型
// 如果想灵活指定父类中T类型，子类也需要变类模板
template <class T1, class T2>
class Son2 : public Base<T2>
{
public:
    Son2()
    {
        cout << "T1的类型为：" << typeid(T1).name() << endl;
        cout << "T2的类型为：" << typeid(T2).name() << endl;
    }
    T1 obj;
};

void test02()
{
    Son2<int, char> s2;
}

int main()
{
    test01();
    test02();
    return 0;
}