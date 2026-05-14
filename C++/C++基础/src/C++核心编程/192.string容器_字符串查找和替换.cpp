#include <iostream> //查找和替换
#include <string>
using namespace std;

void test01()
{ // 查找
    string str = "abcdefgde";
    int pos = str.find("de");
    if (pos == -1)
    {
        cout << "未找到字符串！" << endl;
    }
    else
    {
        cout << "已找到字符串，pos = " << pos << endl;
    }

    string str1 = "abcdefgde";
    int pos = str1.find("de");
    if (pos == -1)
    {
        cout << "未找到字符串！" << endl;
    }
    else
    {
        cout << "已找到字符串，pos = " << pos << endl;
    }
    // rfind，rfind和find区别：rfind从右往左查找、find从左往右查找
    pos = str1.rfind("de");
    cout << "pos = " << pos << endl;
}

void test02()
{ // 替换
    string str1 = "abcdefgde";
    str1.replace(1, 3, "1111"); // 从1号位置起的3个字符替换为"1111"
    cout << "str1 = " << str1 << endl;
}

int main()
{
    test01();
    test02();
    system("pause");
    return 0;
}