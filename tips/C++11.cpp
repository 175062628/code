#include<bits/stdc++.h>
using namespace std;
// auto和decltype

// 列表初始化
class A {
public:
	A(int){}
};
vector<int> f0(){
	A a{123};	// C++11
	A aa={123};	// 原
	int b{123};	// C++11
	return {};	// C++11
}
/* 	列表初始化的一些规则：
 *	首先说下聚合类型可以进行直接列表初始化
 *	类型是一个普通数组，如int[5]，char[]，double[]等
 *
 *	类型是一个类，且满足以下条件：
 *	没有用户声明的构造函数
 *	没有用户提供的构造函数(允许显示预置或弃置的构造函数)
 *	没有私有或保护的非静态数据成员
 *	没有基类
 *	没有虚函数
 * 	没有{}和=直接初始化的非静态数据成员
 * 	没有默认成员初始化器
 */
struct AA {
	int a;
	int b;
	virtual void func() {} // 含有虚函数，不是聚合类
};
		
struct Base {};
struct B : public Base { // 有基类，不是聚合类
	int a;
	int b;
};
		
struct C {
	int a;
	int b = 10; // 有等号初始化，不是聚合类
};
		
struct D {
	int a;
	int b;
private:
	int c; // 含有私有的非静态数据成员，不是聚合类
};
		
struct E {
	int a;
	int b;
	E() : a(0), b(0) {} // 含有默认成员初始化器，不是聚合类
};
// 右值引用
int f(){
	int a=4;
	int &b=a; 	// 左值引用
	int &&c=4;	// 右值引用
	//int &d=4;	// 报错
	cout<<a<<" "<<b<<" "<<c<<endl;
}
// 移动语义
class AAA {
public:
	AAA(int size) : size_(size) {
		data_ = new int[size];
	}
	AAA(){}
	AAA(const AAA& a) {
		size_ = a.size_;
		// 深拷贝
		data_ = new int[size_];
		// need memcpy
		cout << "copy " << endl;
	}
	AAA(AAA&& a) {
		// 把a的所有权转给新的A对象
		this->data_ = a.data_;
		a.data_ = nullptr;
		cout << "move " << endl;
	}
	~AAA() {
		if (data_ != nullptr) {
			delete[] data_;
		}
	}
	int *data_;
	int size_;
};

// 完美转发
void PrintV(int &t) {
	cout << "lvalue" << endl;
}
		
void PrintV(int &&t) {
	cout << "rvalue" << endl;
}
// T&&为万能引用，传入左值则为左值引用，传入右值则为右值引用
// 若类型已被指定，如int等，则解释为右值引用
template<typename T>
void Test(T &&t) {
	PrintV(t);
	PrintV(forward<T>(t));
	PrintV(move(t));
}
void test(){
	Test(1); // lvalue rvalue rvalue
	int a = 1;
	Test(a); // lvalue lvalue rvalue
	Test(forward<int>(a)); // lvalue rvalue rvalue
	Test(forward<int&>(a)); // lvalue lvalue rvalue
	Test(forward<int&&>(a)); // lvalue rvalue rvalue
}
// 使用forward()后所有的类型都已其传入的类型转发给了目标函数
// 如传入1，其应为右值，而经过T&&后，将赋值给了t，同时解释为左值，而使用了forward()后，重新将其解释为了右值
// 在forward中还可以指定转发的类型，如传入a，本来解释为左值，但是加了<int>或<int&&>后可以解释为右值

// 返回值优化
// 本质上避免了返回值的临时对象构造和目标的拷贝构造
// 写法：正常写就行
