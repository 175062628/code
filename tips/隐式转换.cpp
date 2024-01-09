#include<bits/stdc++.h>
using namespace std;
// 隐式转换
class A{
public:
	A(int x=0):x(x){}
	explicit A(int x,int y=3):x(x),y(y){} // 没有explict会报错，因为有默认参数
	void show(){
		cout<<x<<" "<<y<<endl;
	}
private:
	int x=0,y=0;
};
int main(){
	// 隐式转换
	A a=4;
	a.show();
}
