#include<bits/stdc++.h>
using namespace std;
// 基本形式
// [capture](parameters) -> return_type { body }
int test(){
	// 使用Lamda表达式实现递归
	auto f=[](auto&& self,int x)->int{
		if(x){
			return x+self(self,x-1);
		}
		else return 0;
	};
	return f(f,10);// 55
}
// 捕获列表详解
//	[&](parameters) -> return_type { body }
//	引用捕获同一作用域内的所有参数，可以直接使用并修改参数的值
int f0(int x){
	auto f=[&]()->void{
		x--;
	};
	f();
	return x;// 4
}
//	[=](parameters) -> return_type { body }
//	取同一作用域内的所有参数值，但是函数体内无法对参数值进行修改(类似于无法修改值的值传递)
int f1(int x){
	auto f=[=]()->void{
		cout<<x<<endl;
		//x--;	// 报错
		cout<<x<<endl;
	};
	f();
	// 若想在函数体内对捕获参数进行值修改，使用mutable关键字(函数的值传递)
	auto t=[=]()mutable->void{
		cout<<x<<endl;	// 5
		x--;
		cout<<x<<endl;	// 4
	};
	t();
	return x;	// 5
}
//	[var](parameters) -> return_type { body }
//	捕获变量var(值捕获)，可以添加&变成引用捕获
//	此捕获方式可以与上述两种捕获混用，如：
//	[=,&var](parameters) -> return_type { body }
//	表示值捕获其他变量，而引用捕获var

int main(){
	cout<<f1(5);
}
