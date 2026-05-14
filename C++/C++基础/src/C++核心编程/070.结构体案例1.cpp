#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//学生结构体
struct Student
{
    string sName; //姓名
    int score;    //分数
};

//老师结构体
struct Teacher
{
    string tName;             //姓名
    struct Student sArray[5]; //学生数组
};

//创建数据——给老师和学生赋值的函数
void allocateSpace(struct Teacher tArray[], int len) //struct可以省略
{
    string tName = "老师"; // Teacher_
    string sName = "学生";
    string nameSeed = "ABCDE";
    //给老师进行赋值
    for (int i = 0; i < len; i++)
    {
        tArray[i].tName = tName + nameSeed[i]; //老师姓名
        //通过循环给每名老师所带的学生进行赋值
        for (int j = 0; j < 5; j++)
        {
            tArray[i].sArray[j].sName = sName + nameSeed[j];
            tArray[i].sArray[j].score = rand() % 61 + 40; // 0~60 40~100
            // rand() % 60：0~59
        }
    }
}

//打印数据——打印所有信息
void printTeachers(struct Teacher tArray[], int len) //struct可以省略
{
    for (int i = 0; i < len; i++)
    {
        cout << "老师的姓名：" << tArray[i].tName << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "\t学生姓名：" << tArray[i].sArray[j].sName << "；考试分数：" << tArray[i].sArray[j].score << endl;
        }
    }
}

int main()
{
    //利用系统时间，产生随机数
    srand((unsigned int)time(NULL)); //随机数种子 头文件 #include <ctime>

    //1、创建3名老师的数组
    struct Teacher tArray[3]; //老师数组 struct可以省略

    //2、通过函数给3名老师的信息赋值，并给老师带的学生信息赋值
    cout << "string类型所占内存空间为：" << sizeof(string) << endl; //string类型所占内存空间为：32
    cout << "int类型所占内存空间为：" << sizeof(int) << endl; //int类型所占内存空间为：4
    cout << "sizeof(tArray)：" << sizeof(tArray) << endl;            //sizeof(tArray)：696
    cout << "sizeof(Teacher)：" << sizeof(Teacher) << endl;          //sizeof(Teacher)：232
    cout << "sizeof(Student)：" << sizeof(Student) << endl;          //sizeof(Student)：40
    cout << "sizeof(tArray[0])：" << sizeof(tArray[0]) << endl;      //sizeof(tArray[0])：232
    int len1 = sizeof(tArray) / sizeof(Teacher);                     //计算数组长度
    cout << "len1：" << len1 << endl;                                //len1：3
    int len2 = sizeof(tArray) / sizeof(tArray[0]);                   //计算数组长度
    cout << "len2：" << len2 << endl;                                //len2：3
    allocateSpace(tArray, len2);                                     //创建数据

    //3、打印所有老师及所带的学生信息
    printTeachers(tArray, len2); //打印数据

    system("pause");
    return 0;
}