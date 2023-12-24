#include<bits/stdc++.h>
using namespace std;
// 合并若干个区间，并返回合并结果
vector<vector<int>> merge(vector<vector<int>>& intervals) {
	sort(intervals.begin(),intervals.end());
	vector<vector<int>> res;
	vector<int> target=intervals[0];
	for(int i=0;i<intervals.size()-1;i++){
		if(target[1]<intervals[i+1][0]){
			res.push_back(target);
			target=intervals[i+1];
		}
		else{
			if(target[1]<intervals[i+1][1]){
				target[1]=intervals[i+1][1];
			}
		}
	}
	res.push_back(target);
	return res;
}
