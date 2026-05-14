#include <iostream>
#include <string>
using namespace std;

//1、设计英雄结构体
//英雄结构体
struct hero
{
    string name; //姓名
    int age;     //年龄
    string sex;  //性别
};

//冒泡排序——实现年龄升序排列
void bubbleSort(struct hero arr[], int len) //struct可省
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            //如果j下标的元素年龄大于j+1下标的元素的年龄，交换两个元素
            if (arr[j].age > arr[j + 1].age)
            {
                struct hero temp = arr[j]; //临时数据
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//打印数组——打印排序后数组中的信息
void printHeros(struct hero arr[], int len) //struct可省
{
    for (int i = 0; i < len; i++)
    {
        cout << "姓名：" << arr[i].name << "\t性别：" << arr[i].sex << "\t年龄：" << arr[i].age << endl;
    }
}

//1、设计英雄结构体
//2、创建数组存放5名英雄
//3、对数组进行排序，按照年龄进行升序排序
//4、将排序后的结果打印输出
int main()
{
    //2、创建数组存放5名英雄
    struct hero heroArray[5] =
        {
            {"刘备", 23, "男"},
            {"关羽", 22, "男"},
            {"张飞", 20, "男"},
            {"赵云", 21, "男"},
            {"貂蝉", 19, "女"}};

    cout << "string类型所占内存空间为：" << sizeof(string) << endl;   //string类型所占内存空间为：32
    cout << "int类型所占内存空间为：" << sizeof(int) << endl;         //int类型所占内存空间为：4
    cout << "sizeof(heroArray)：" << sizeof(heroArray) << endl;       //sizeof(heroArray)：360
    cout << "sizeof(heroArray[0])：" << sizeof(heroArray[0]) << endl; //sizeof(heroArray[0])：72
    cout << "sizeof(hero)：" << sizeof(hero) << endl;                 //sizeof(hero)：72

    int len1 = sizeof(heroArray) / sizeof(heroArray[0]); //整体所占空间大小/单个元素所占空间大小
    cout << "len1：" << len1 << endl;                    //len1：5
    int len2 = sizeof(heroArray) / sizeof(hero);         //获取数组元素个数
    cout << "len2：" << len2 << endl;                    //len1：5

    cout << "排序前，数组打印：" << endl;
    for (int i = 0; i < len1; i++)
    {
        cout << "姓名：" << heroArray[i].name << "\t性别：" << heroArray[i].sex << "\t年龄：" << heroArray[i].age << endl;
    }

    //3、对数组进行排序，按照年龄进行升序排序
    bubbleSort(heroArray, len1); //排序

    cout << "排序后，数组打印：" << endl;

    //4、将排序后的结果打印输出
    printHeros(heroArray, len1); //打印

    system("pause");
    return 0;
}