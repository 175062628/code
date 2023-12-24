#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> divide(vector<int>& nums){
	sort(nums.begin(),nums.end());
	vector<vector<int>> res;
	int l=0,h=0,n=nums.size();
	for(;h<n-1;h++){
		while(h<n-1&&nums[h]==nums[h+1]){
			h++;
		}
		res.push_back({l,h});
		l=h+1;
	}
	if(nums[n-1]!=nums[n-2]){
		res.push_back({n-1,n-1});
	}
	return res;
}
