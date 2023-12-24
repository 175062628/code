#include<bits/stdc++.h>
using namespace std;
int Manacher(string s){
	string t="$#";
	for(auto& c:s){
		t+=c;
		t+='#';
	}
	t+='!';
	int n=t.length(),res=0,ci=1,mi=1;
	vector<int> v(n,1);
	for(int i=1;i<n;i++){
		int sum=1;
		if(i<=mi) sum=min(v[2*ci-i],mi-i+1);
		while(t[i-sum]==t[i+sum]) sum++;
		v[i]=sum;
		if(i+sum-1>mi){
			mi=i+sum-1;
			ci=i;
		}
		res+=v[i]/2;
	}
	return res;
}
