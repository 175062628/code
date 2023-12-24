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
ff(3.3,f);  // 3.3 3
ff(3.3);	// 3.3 0

// 类继承示例
class Animal{
public:
	Animal(){}
	// 不要设置默认参数
	Animal(int w):weight(w){}
	Animal(int w,int h):weight(w),height(h){}
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
	Dog(string name):name(name),Animal(){}// 显示调用基类构造函数
	Dog(string name,int w,int h):name(name),Animal(w,h){}
	void bark(){
		cout<<"barking"<<endl;
	}
private:
	string name;
};

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

// 生成序号
vector<int> index(n);
iota(index.begin(),index.end(),0);
// 匿名函数
auto f=[](typename parameters)->typename{
	return ;
};
// 匿名函数递归
auto f=[](auto&& self,typename parameters)->typename{
	return self(self,parameters);
};
f(f,typename);
// 排序
sort(vector<typename>.begin(),vector<typename>.end(),[](typename a,typename b){
	return a<b;
});
// 优先队列
auto cmp=[](typename a,typename b)->bool{
	return a<b;
};
priority_queue<typename,vector<typename>,decltype(cmp)> pq(cmp);
pq.push(typename);
pq.top();
pq.pop();
// 双端队列
deque<typename> dq;
dq.push_back(typename);
dq.pop_back();
dq.push_front(typename);
dq.pop_front();
// 哈希
unordered_map<typename,typename> um;
map<typename,typename> m;
m.emplace({typename,typename});
m[typename]=typename;
for(auto& [x,y]:m){}
// 集合
unordered_set<typename> us;
set<typename> s;
s.emplace(typename);
s.count(typename);
// 栈
stack<typename> s;
s.empty();
s.push(typename);
s.pop();
// 二分查找
	// 大于等于a的最小值
lower_bound(vector<typename>.begin(),vector<typename>.end(),typename a);
	// 大于a的最小值
upper_bound(vector<typename>.begin(),vector<typename>.end(),typename a);
// 位运算
x >> k;
x << k;
x |= k;
x &= k;
x ^= k;
