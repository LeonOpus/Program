#include <iostream> //继承写法
using namespace std;

// 继承的好处：减少重复代码。
// 语法：class 子类 : 继承方式 父类 {}
// 子类也称为派生类,父类也称为基类。

class BasePage
{ // 公共页面类，继承实现页面
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
};

class Java : public BasePage
{ // Java页面
public:
	void content()
	{
		cout << "JAVA学科视频" << endl;
	}
};

class Python : public BasePage
{ // Python页面
public:
	void content()
	{
		cout << "Python学科视频" << endl;
	}
};

class CPP : public BasePage
{ // C++页面
public:
	void content()
	{
		cout << "C++学科视频" << endl;
	}
};

void test01()
{
	// Java页面
	cout << "Java下载视频页面如下： " << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "--------------------" << endl;

	// Python页面
	cout << "Python下载视频页面如下： " << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	cout << "--------------------" << endl;

	// C++页面
	cout << "C++下载视频页面如下： " << endl;
	CPP cp;
	cp.header();
	cp.footer();
	cp.left();
	cp.content();
}

int main()
{
	test01();
	return 0;
}