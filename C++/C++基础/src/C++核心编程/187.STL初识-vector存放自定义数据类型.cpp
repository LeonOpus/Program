#include <iostream>//vector容器中存放自定义数据类型
#include <vector>
#include <string>
using namespace std;

//自定义数据类型
class Person {
    public:
        Person(string name, int age) {
            mName = name;
            mAge = age;
        }
    public:
        string mName;
        int mAge;
};

//存放对象
void test01() {
    vector<Person> v;
    //创建数据
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    Person p5("eee", 50);
    v.push_back(p1);//向容器中添加数据
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    //遍历容器中的数据
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it+=1) {
        cout << "姓名Name：" << (*it).mName << "，年龄Age：" << (*it).mAge << endl;
        cout << "姓名Name：" << it->mName << "，年龄Age：" << it->mAge << endl;
    }
}

//存放自定义数据类型(对象指针)
void test02() {
    vector<Person *> v;
    //创建数据
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    Person p5("eee", 50);
    v.push_back(&p1);//向容器中添加数据
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);
    //遍历容器中的数据
    for (vector<Person *>::iterator it = v.begin(); it != v.end(); it++) {
        Person *p = (*it);
        cout << "Name：" << p->mName << "，Age：" << (*it)->mAge << endl;
    }
}

int main() {
    test01();
    test02();
    return 0;
}