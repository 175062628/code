#include<bits/stdc++.h>
using namespace std;
int KMP(string& target,string& pattern){
	int m=target.length(),n=pattern.length();
	auto f=[&]()->vector<int>{
		vector<int> next={0};
		for(int i=1,j=0;i<pattern.length();i++){
			while(j>0&&pattern[j]!=pattern[i]) j=next[j - 1];
			if(pattern[i]==pattern[j]) j++; 
			next.push_back(j);
		}
		return next;
	};
	
	vector<int> next=f();
	for(int i=0,j=0;i<target.length();i++){
		while(j>0 && target[i]!=pattern[j]) j=next[j - 1];
		if(target[i]==pattern[j]) j++;
		if(j==pattern.length()){
			return i-j+1;
			// 多次匹配就添加 j=next[j-1];
		}
	}
	return -1;
}
