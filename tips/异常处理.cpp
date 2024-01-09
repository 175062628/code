#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Error{
public:
	Error(string s):message(s){}
	void show(){
		// cerr输出不经过缓冲区，处理异常时应使用cerr而不是cout
		cerr<<message<<endl;
	}
private:
	string message;
};
// 抛出异常类Error
void f0(int x){
	if(!x){
		throw new Error("x要大于0！");
	}
	cout<<x<<endl;
}
void test0(int x){
	try{
		f0(x);
	} catch(Error* e) {
		e->show();
	}
}
// 抛出一段字符串
void f1(int x){
	if(x){
		throw "x不能大于0！";
	}
	cout<<x<<endl;
}
void test1(int x){
	try{
		f1(x);
		// 处理异常捕获字符串时必须为 const char*
	} catch(const char* s) {
		cerr<<s<<endl;
	}
}
int main(){
	test0(0);
	test1(1);
}
