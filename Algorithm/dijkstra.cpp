#include<bits/stdc++.h>
using namespace std;
#define inf 99999

// edges形如{{x1,y1,d1},{x2,y2,d2}}，有向图
int dijkstra(vector<vector<int>>& edges,int n,int from,int to){
	vector<vector<pair<int,int>>> v(n);
	for(auto& x:edges){
		v[x[0]].push_back({x[1],x[2]});
	}
	vector<int> visited(n,0),distances(n,inf),path(n,-1);
	distances[from]=0;
	for(auto& [y,d]:v[from]){
		distances[y]=d;
		path[y]=from;
	}
	for(int _=0;_<n;_++){
		int pos=-1;
		for(int i=0;i<n;i++){
			if(!visited[i]&&(pos<0||distances[i]<distances[pos])){
				pos=i;
			}
		}
		visited[pos]=1;
		for(int i=0;i<v[pos].size();i++){
			auto [y,d]=v[pos][i];
			if(visited[y]) continue;
			if(distances[y]>distances[pos]+d){
				distances[y]=distances[pos]+d;
				path[y]=pos;
			}
		}
	}
	return distances[to]==inf?-1:distances[to];
}

// matrix形如：
// [0,inf,8]
// [4,0,7]
// [inf,4,0]
int dijkstra(vector<vector<int>>& matrix,int from,int to){
	int n=matrix.size();
	vector<int> visited(n,0),distances(n,inf),path(n,-1);
	for(int i=0;i<n;i++){
		if(matrix[from][i]==inf) continue;
		distances[i]=matrix[from][i];
	}
	for(int _=0;_<n;_++){
		int pos=-1;
		for(int i=0;i<n;i++){
			if(!visited[i]&&(pos<0||distances[i]<distances[pos])){
				pos=i;
			}
		}
		visited[pos]=1;
		for(int i=0;i<n;i++){
			if(visited[i]) continue;
			if(distances[i]>distances[pos]+matrix[pos][i]){
				distances[i]=distances[pos]+matrix[pos][i];
				path[i]=pos;
			}
		}
	}
	return distances[to]==inf?-1:distances[to];
}
