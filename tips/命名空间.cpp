#include<iostream>
#include<bits/stdc++.h>
using namespace std;
namespace A{
	void show(){
		cout<<"1"<<endl;
	}
}
namespace B{
	void show(){
		cout<<"0"<<endl;
	}
}
int main(){
	A::show(); // 1
	B::show(); // 0
	show(); // 报错
}
