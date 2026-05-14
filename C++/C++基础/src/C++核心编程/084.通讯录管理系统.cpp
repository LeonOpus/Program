#include <iostream>
#include <string>
using namespace std;

// 设计联系人的结构体
struct Person
{
    string m_name;
    int m_gender;
    int m_age;
    string m_phone;
    string m_address;
};
// 设计通讯录的结构体
#define MAX 1000 // 最大人数
struct AddressBook
{
    struct Person personArray[MAX]; // 通讯录最多有1000个联系人
    int m_size;                     // 记录当前通讯录有多少个联系人
};
// 检测联系人是否存在，如果存在，返回联系人所在数组的具体位置，不存在则返回-1
int isExist(AddressBook *ads, string name)
{
    for (int i = 0; i < ads->m_size; i++)
    {
        if (ads->personArray[i].m_name == name)
        {
            return i;
        }
    }
    return -1;
}
// 1.添加联系人
void addPerson(AddressBook *ads) // 指针来接收地址
{
    // 判断通讯录是否已满，满了就不允许添加
    if (ads->m_size == MAX)
    {
        cout << "通讯录已满，无法添加" << endl;
        return;
    }
    else
    {
        // 添加联系人
        // 1.姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        ads->personArray[ads->m_size].m_name = name;
        // 2.性别
        int gender;
        cout << "请输入性别：" << endl;
        cout << "男(1) 女(2)" << endl;
        while (true)
        {
            cin >> gender;
            if (gender == 1 || gender == 2)
            {
                ads->personArray[ads->m_size].m_gender = gender;
                break;
            }
            cout << "输入有误，请重新输入" << endl;
        }

        // 3.年龄
        cout << "请输入年龄：" << endl;
        int age;
        while (true)
        {
            cin >> age;
            if (age >= 0)
            {
                ads->personArray[ads->m_size].m_age = age;
                break;
            }
            cout << "输入有误，请重新输入" << endl;
        }

        // 4.电话
        cout << "请输入电话：" << endl;
        string phone;
        while (true)
        {
            cin >> phone;
            if (phone.length() >= 10)
            {
                ads->personArray[ads->m_size].m_phone = phone;
                break;
            }
            cout << "输入有误，请重新输入" << endl;
        }

        // 5.地址
        cout << "请输入地址：" << endl;
        string address;
        cin >> address;
        ads->personArray[ads->m_size].m_address = address;

        // 更新通讯录人数
        ads->m_size++;
        cout << "添加成功" << endl;
        system("pause");
        system("cls");
    }
}

// 2. 删除联系人
void deletePerson(AddressBook *ads)
{
    // 删除联系人实现步骤
    // 1.封装检测联系人是否存在
    // 2.封装删除联系人函数
    // 3.测试删除联系人功能
    cout << "请输入待删除联系人的姓名：" << endl;
    string name;
    cin >> name;
    // ret==-1 表示联系人不存在

    int ret = isExist(ads, name);
    if (ret != -1)
    {
        for (int i = ret; i < ads->m_size; i++)
        {
            // 数据迁移
            ads->personArray[i] = ads->personArray[i + 1];
        }
        ads->m_size--; // 更新通讯录中的人员
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}
// 3. 修改联系人
void updatePerson(AddressBook *ads)
{
    cout << "请输入要修改的联系人：" << endl;
    string name;
    cin >> name;

    int ret = isExist(ads, name);
    if (ret != -1)
    {
        // 姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        ads->personArray[ret].m_name = name;
        // 性别
        cout << "请输入性别：" << endl;
        int gender;
        cin >> gender;
        ads->personArray[ret].m_gender = gender;
        // 年龄
        cout << "请输入年龄：" << endl;
        int age;
        cin >> age;
        ads->personArray[ret].m_age = age;
        // 电话号码
        cout << "请输入电话号码：" << endl;
        string phone;
        cin >> phone;
        ads->personArray[ret].m_phone = phone;
        // 住址
        cout << "请输入住址：" << endl;
        string address;
        cin >> address;
        ads->personArray[ret].m_address = address;
    }
    else
    {
        cout << "查无此人" << endl;
    }

    system("pause");
    system("cls");
}

// 4. 查找联系人
void findPerson(AddressBook *ads)
{
    cout << "请输入要查找联系人姓名" << endl;
    string name;
    cin >> name;

    // 判断指定的联系人是否存在于通讯录中
    int ret = isExist(ads, name);
    if (ret != -1)
    {
        cout << "姓名：" << ads->personArray[ret].m_name << "\t";
        cout << "性别：" << ads->personArray[ret].m_gender << "\t";
        cout << "年龄：" << ads->personArray[ret].m_age << "\t";
        cout << "电话：" << ads->personArray[ret].m_phone << "\t";
        cout << "住址：" << ads->personArray[ret].m_address << "\t";
    }
    else
    {
        cout << "查无此人" << endl;
    }
    cout << "修改联系人成功" << endl;
    system("pause");
    system("cls");
}
// 5. 显示联系人
void showPerson(AddressBook *ads)
{
    // 判断通讯录支付人数是否为空
    // 如果不为空，显示记录的联系人信息
    if (ads->m_size == 0)
    {
        cout << "通讯录为空" << endl;
    }
    else
    {
        for (int i = 0; i < ads->m_size; i++)
        {
            cout << "姓名：" << ads->personArray[i].m_name << endl;
            cout << "性别：" << (ads->personArray[i].m_gender == 1 ? "男" : "女") << endl;
            cout << "年龄：" << ads->personArray[i].m_age << endl;
            cout << "电话：" << ads->personArray[i].m_phone << endl;
            cout << "地址：" << ads->personArray[i].m_address << endl;
        }
    }
    cout << "按回车键继续..." << endl;
    system("pause");
    system("cls");
}
// 6. 清空联系人
void cleanPerson(AddressBook *ads)
{
    ads->m_size = 0; // 逻辑清空即可 不用在数组里全部抹除
    cout << "通讯录已清空" << endl;
    system("pause");
    system("cls");
}
// 封装函数显示该界面 比如void showMeum()
void showMeum()
{
    cout << "************************" << endl;
    cout << "***** 1.添加联系人 *****" << endl;
    cout << "***** 2.删除联系人 *****" << endl;
    cout << "***** 3.修改联系人 *****" << endl;
    cout << "***** 4.查找联系人 *****" << endl;
    cout << "***** 5.显示联系人 *****" << endl;
    cout << "***** 6.清空联系人 *****" << endl;
    cout << "***** 0.退出通讯录 *****" << endl;
    cout << "************************" << endl;
}

int main()
{
    // system("chcp 65001");
    //  创建通讯录结构体
    AddressBook ads;
    // 初始化通讯录结构体
    ads.m_size = 0;
    cout << "欢迎使用通讯录管理系统" << endl;
    cout << "请输入你的选择：" << endl;
    int choice = 0;
    while (true)
    {
        showMeum(); // 在main函数调用封装好的函数
        cin >> choice;
        switch (choice)
        {
        case 1: // 添加联系人
                // 值传递不会修饰实参，因此要加&才能取到地址真正修饰这个数据，&ad地址传递
            addPerson(&ads);
            break;
        case 2: // 删除联系人
        {
            // cout << "请输入要删除的人的姓名：" << endl;
            // string name;
            // cin >> name;
            // if (isExist(&ads, name) == -1)
            //     cout << "查无此人" << endl;
            // else
            // {
            //     cout << "找到此人" << endl;
            // }
            deletePerson(&ads);
            break;
        }
        case 3: // 修改联系人
            updatePerson(&ads);
            break;
        case 4: // 查找联系人
            findPerson(&ads);
            break;
        case 5:
            showPerson(&ads);
            break;
        case 6:
            cleanPerson(&ads);
            break;
        case 0:
            cout << "欢迎下次使用" << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}
