#include<bits/stdc++.h>
using namespace std;
// 埃氏筛 O(nloglogn)
int primes(int n){
	vector<int> prime(n,1);
	int res=0;
	for(int i=2;i<n;i++){
		if(!prime[i]) continue;
		res++;
		for(long long j=1ll*i*i;j<n;j+=i){
			prime[j]=0;
		}
	}
	return res;
}
// 线性筛 O(n)
int IsPrimes(int n){
	vector<int> prime(n,1),res;
	for(int i=2;i<n;i++){
		if(prime[i]) res.push_back(i);
		for(int j=0;j<res.size()&&i*res[j]<n;j++){
			prime[i*res[j]]=0;
			if(i%res[j]==0) break;
		}
	}
	return res.size();
}
