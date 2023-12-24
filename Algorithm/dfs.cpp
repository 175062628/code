#include<bits/stdc++.h>
using namespace std;
void dfs(vector<vector<int>>& matrix,vector<vector<int>>& visited,int row,int arr,int& res){
	auto other_limited=[]()->bool{
		return;
	};
	int m=matrix.size(),n=matrix[0].size();
	visited[row][arr]=1;
	vector<vector<int>> directions={{1,0},{-1,0},{0,1},{0,-1}};
	for(auto& dir:directions){
		int nx=row+dir[0],ny=arr+dir[1];
		if(0<=nx&&nx<m && 0<=ny&&ny<n && !visited[nx][ny] && other_limited){
			res++;
			dfs(matrix,visited,nx,ny,res);
		}
	}
}
