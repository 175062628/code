#include<bits/stdc++.h>
using namespace std;
// 快排
void qsort(vector<int>& nums,auto f=[](int& a,int& b)->bool{
	return a<b;
};){
	auto f=[](auto&& self,vector<int>& nums,int l,int h)->void{
		int e=nums[l],i=l,j=h;
		while(i<j){
			while(i<j&&e<nums[j]) j--;
			if(i<j) nums[i++]=nums[j];
			while(i<j&&nums[i]<e) i++;
			if(i<j) nums[j--]=nums[i];
		}
		nums[i]=e;
		if(l<i-1) self(self,nums,l,i-1);
		if(i+1<h) self(self,nums,i+1,h);
	};
	f(f,nums,0,nums.size()-1);
}
// 归并
void msort(vector<int>& nums){
	auto merge=[](vector<int>& nums,int l,int m,int h)->void{
		int i=l,j=m+1;
		vector<int> res;
		while(i<=m&&j<=h){
			if(nums[i]<nums[j]) res.push_back(nums[i++]);
			else res.push_back(nums[j++]);
		}
		while(i<=m) res.push_back(nums[i++]);
		while(j<=h) res.push_back(nums[j++]);
		for(int i=l;i<=h;i++) nums[i]=res[i-l];
	};
	auto f=[merge](auto&& self,vector<int>& nums,int l,int h)->void{
		if(l<h){
			int m=(l+h)/2;
			self(self,nums,l,m);
			self(self,nums,m+1,h);
			merge(nums,l,m,h);
		}
	};
	f(f,nums,0,nums.size()-1);
}
