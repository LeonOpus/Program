#include <iostream>
#include <string>
using namespace std;

/*
string构造函数原型：
1、string(); //创建一个空的字符串，例如：string str;
2、string(const char* s); //使用字符串s初始化
3、string(const string& str); //使用一个string对象初始化另一个string对象
4、string(int n, char c); //使用n个字符c初始化
*/

//string的构造函数
void test01() {
    string s1;//创建空字符串，调用默认无参构造函数
    cout << "str1 = " << s1 << endl;//str1 =

    const char *str = "hello world";
    string s2(str);//把c_string转换成了string
    cout << "str2 = " << s2 << endl;//str2 = hello world
  
    string s3(s2);//调用拷贝构造函数
    cout << "str3 = " << s3 << endl;//str2 = hello world

    string s4(10, 'a');
    cout << "str4 = " << s4 << endl;//str4 = aaaaaaaaaa
}

int main() {
    test01();
    return 0;
}