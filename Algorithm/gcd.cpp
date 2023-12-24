#include<bits/stdc++.h>
using namespace std;
// 更相减损法
int gcd1(int x,int y){
	if(x==y) return x;
	if(x>y) return gcd1(x-y,y);
	else return gcd1(y-x,x);
}
// 辗转相除法
int gcd2(int x,int y){
	if(y==0) return x;
	return gcd2(y,x%y);
}
