#include<bits/stdc++.h>
using namespace std;
int bag(vector<int>& values,vector<int>& weights,int capacity){
	int n=values.size();
	vector<vector<int>> res(n+1,vector<int>(capacity+1,0));
	for(int i=1;i<=n;i++){
		for(int j=0;j<=capacity;j++){
			if(j-weights[i-1]>=0){
				res[i][j]=max(res[i-1][j],res[i-1][j-weights[i-1]]+values[i-1]);
			}
			else{
				res[i][j]=res[i-1][j];
			}
		}
	}
	return res[n][capacity];
}
