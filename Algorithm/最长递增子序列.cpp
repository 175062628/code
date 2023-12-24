#include<bits/stdc++.h>
using namespace std;
// O(n^2)
int lengthOfLIS_(vector<int>& nums){
	int n=nums.size();
	vector<int> res(n,1);
	res[0]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			if(nums[j]<nums[i]){
				res[i]=max(res[j]+1,res[i]);
			}
		}
	}
	return *max_element(res.begin(),res.end());
}
// O(nlogn)
int lengthOfLIS(vector<int>& nums){
	vector<int> res={nums[0]};
	for(int i=1;i<nums.size();i++){
		auto it=lower_bound(res.begin(),res.end(),nums[i]);
		if(it==res.end()) res.push_back(nums[i]);
		else *it=nums[i];
	}
	return res.size();
}
