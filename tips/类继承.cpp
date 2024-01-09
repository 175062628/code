#include<bits/stdc++.h>
using namespace std;
// 类继承示例
class Animal{
public:
	Animal(){}
	// 设置默认参数时要确保编译器能找到正确的构造函数
	Animal(int w):weight(w){}
	Animal(int w,int h=0):weight(w),height(h){}
	void sleep(){
		cout<<"sleeping"<<endl;
	}
	void eat(){
		cout<<"eating"<<endl;
	}
	void revise(int w,int h){
		weight=w;
		height=h;
	}
	void show(){
		cout<<"height:"<<height<<endl<<"weight:"<<weight<<endl; 
	}
protected:
	int weight;
	int height;
};
class Dog:public Animal{
public:
	Dog(string name):name(name),Animal(){} // 显示调用基类构造函数
	Dog(string name,int w,int h):name(name),Animal(w,h){}
	void bark(){
		cout<<"barking"<<endl;
	}
private:
	string name;
};
// final和override
// 被final修饰的无法被继承，但是可以在类内声明虚函数
class A{
public:
	A(int val):a(val){}
	virtual void show(){
		cout<<"A"<<endl;
	}
private:
	int a;
};
class B:public A{
public:
	B(int val):A(val){}
	void show() override {
		cout<<"B"<<endl;
	}
	/*void exhibit()override{	// 报错，基类中没有exhibit
		cout<<"BB"<<endl;
	  }*/
};
