#include<bits/stdc++.h>
using namespace std;
// 函数指针示例
int t(double x){
	return 0;
}
int f(double x){
	return x;
}
void ff(double x,int (*p)(double)=t){
	cout<<x<<" "<<(*p)(x)<<endl;
}
int main(){
	ff(3.3,f);  // 3.3 3
	ff(3.3);	// 3.3 0
}
