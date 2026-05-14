#include <iostream>
#include <string>
using namespace std;

//类模板
template <class NameType, class AgeType = int>
class Person {
    public:
        Person(NameType name, AgeType age) {
            this->mName = name;
            this->mAge = age;
        }
        void showPerson() {
            cout << "name：" << this->mName << "，age：" << this->mAge << endl;
        }
    public:
        NameType mName;
        AgeType mAge;
};

//区别1、类模板没有自动类型推导的使用方式
void test01() {
    //Person p("孙悟空", 1000);//错误，类模板使用时不可以用自动类型推导。错误，无法用自动类型推导
    Person<string, int> p("孙悟空", 1000);//必须使用显示指定类型的方式使用类模板。正确，只能用显示指定类型
    p.showPerson();
}

//区别2、类模板在模板参数列表中可以有默认参数
void test02() {
    Person<string> p("猪八戒", 999);//类模板中的模板参数列表可以指定默认参数
    p.showPerson();
}

int main(){
    test01();
    test02();
    return 0;
}