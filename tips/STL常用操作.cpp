#include<bits/stdc++.h>
using namespace std;
// 生成序号
vector<int> index(n);
iota(index.begin(),index.end(),0);
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
// map
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
