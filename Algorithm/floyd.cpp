#include<bits/stdc++.h>
using namespace std;
#define inf 99999
// edges形如{{x1,y1,d1},{x2,y2,d2}},且无{{x1,y1,d1},{x1,y1,d2}}的无向图
vector<vector<int>> floyd(int n,vector<vector<int>>& edges) {
	vector<vector<int>> matrix(n,vector<int>(n,inf));
	for(auto& e:edges){
		int x=e[0],y=e[1],w=e[2];
		matrix[x][y]=w;
		matrix[y][x]=w;
	}
	for (int k=0;k<n;k++){
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]);
			}
		}
	}
	return matrix;
}
