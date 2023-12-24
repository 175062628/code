#include<bits/stdc++.h>
using namespace std;
int bfs(vector<vector<int>>& matrix,int row,int arr){
	auto other_limited=[]()->bool{
		return;
	};
	int res=1,m=matrix.size(),n=matrix[0].size();
	vector<vector<int>> visited(m,vector<int>(n,0)),directions={{1,0},{-1,0},{0,1},{0,-1}};
	visited[row][arr]=1;
	queue<pair<int,int>> q;
	q.push({row,arr});
	while(!q.empty()){
		int sz=q.size();
		for(int i=0;i<sz;i++){
			for(auto& dir:directions){
				int nx=q.front().first+dir[0],ny=q.front().second+dir[1];
				if(0<=nx&&nx<m && 0<=ny&&ny<n && !visited[nx][ny] && other_limited){
					q.push({nx,ny});
					visited[nx][ny]=1;
					res++;
				}
			}
			q.pop();
		}
	}
	return res;
}
