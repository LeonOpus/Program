#include <iostream>
using namespace std;

class Animal
{ // 动物类
public:
	int m_Age;
};

// 利用虚继承解决菱形继承的问题
// 继承之前加上virtual关键字后变为虚继承，此时公共的父类Animal类称为虚基类
class Sheep : virtual public Animal
{
}; // 羊类
class Tuo : virtual public Animal
{
}; // 驼类
class SheepTuo : public Sheep, public Tuo
{
}; // 羊驼类

void test01()
{
	SheepTuo st;
	st.Sheep::m_Age = 100;
	st.Tuo::m_Age = 200;
	// 菱形继承时，两个父类拥有相同数据，需要加以作用域区分
	// 使用虚继承后，数据只有一份！
	cout << "st.Sheep::m_Age = " << st.Sheep::m_Age << endl; // 200
	cout << "st.Tuo::m_Age = " << st.Tuo::m_Age << endl;	 // 200
	// 这份数据我们知道只要有一份就可以，菱形继承导致数据有两份，资源浪费
	cout << "st.m_Age = " << st.m_Age << endl; // 200
}

int main()
{
	test01();
	return 0;
}