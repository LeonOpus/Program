#include <iostream> //构造函数的分类及调用 
using namespace std; 

// 1、构造函数分类 
// 按照参数分类分为：有参构造和无参构造(默认构造)，无参又称为默认构造函数 
// 按照类型分类分为：普通构造和拷贝构造 

class Person 
{ 
public: 
    // 无参（默认）构造函数 
    Person() 
    { 
        cout << "Person的无参构造函数调用!" << endl; 
    } 
    // 有参构造函数 
    Person(int a) 
    { 
        age = a; 
        cout << "Person的有参构造函数调用!" << endl; 
    } 
    // 拷贝构造函数，将p的所有属性拷贝到自身对象中 
    Person(const Person &p) 
    { // 引用的方式传参 
        // 将传入的人身上的所有属性，拷贝到我身上 
        age = p.age; 
        cout << "拷贝构造函数!" << endl; 
    } 

    // 析构函数 
    ~Person() 
    { 
        cout << "析构函数!" << endl; 
    } 

public: 
    int age; 
}; 

// 2、构造函数的调用 
// 调用无参构造函数 
void test01() 
{ 
    Person p; // 调用无参构造函数 
} 

// 调用有参的构造函数 
void test02() 
{ 
    // 2.1、括号法（常用） 
    Person p1;     // 默认构造函数调用，去掉括号
    Person p2(10); // 有参构造函数 
    Person p3(p2); // 拷贝构造函数 
    // 注意事项1：调用默认无参构造函数时不能加括号，如果加了编译器认为这是一个函数声明。Person p2(); 
    cout << "p2的年龄为：" << p2.age << endl; 
    cout << "p3的年龄为：" << p3.age << endl; 

    // 2.2、显式法 
    Person p4;              // 默认构造函数调用 
    Person p5 = Person(10); // 有参构造函数 
    Person p6 = Person(p2); // 拷贝构造函数 

    // Person(10);//单独写就是匿名对象。特点：当前行执行结束之后，马上析构，系统会立即回收掉匿名对象。 
    cout << "aaaaa" << endl; 

    // 2.3、隐式转换法 
    Person p7 = 10; // 相当于写了：Person p7 = Person(10);有参构造，修改变量名避免重复定义
    Person p8 = p7; // Person p8 = Person(p7);拷贝构造，修改变量名避免重复定义

    // 注意事项2：不能利用“拷贝构造函数”初始化匿名对象，编译器认为是对象声明。 
    // Person p5(p4); 
} 

int main() 
{ 
    test01(); 
    // test02(); 
    return 0; 
}