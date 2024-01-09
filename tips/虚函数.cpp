#include<bits/stdc++.h>
using namespace std;
// 意义：实现多态
class A{
public:
	virtual void show(){
		cout<<"A"<<endl;
	}
};
class B:public A{
public:
	void show()override{
		cout<<"B"<<endl;
	}
};
class C:public B{
public:
	void show()override{
		cout<<"C"<<endl;
	}
};
void test(){
	B* a=new C();
	a->show(); // B 体现了多态
	// 若在基类A中不将show声明为虚函数，虽然能重载，但是上式的结果为A，因为没有根据实例类型推断调用哪个show
}

class AA{
public:
	void show(){
		cout<<"A"<<endl;
	}
};
class BB:public AA{
public:
	virtual void show(){
		cout<<"B"<<endl;
	}
};
class CC:public BB{
public:
	void show()override{
		cout<<"C"<<endl;
	}
};
void test0(){
	AA* a=new BB();
	a->show(); // A
	// 因为BB继承AA时才将其声明为虚函数，所以虽然对象的类型是BB，但是调用的是AA的show
}
int main(){
	test0();
}
// 纯虚函数
class f{
public:
	virtual void func()=0;	// 纯虚函数，此时类为抽象类，只能被继承，不能生成实例
};
// 继承抽象类的派生类必须重载这个纯虚函数，否则派生类也是抽象类
// 定义纯虚函数的目的在于，使派生类仅仅只是继承函数的接口
