#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
	int val=0,low,high,lazy=0;
	TreeNode *left,*right;
	TreeNode(int l,int h):low(l),high(h),left(nullptr),right(nullptr){}
	TreeNode(TreeNode* l,TreeNode* r):left(l),right(r){}
};
TreeNode* build(int l,int h,vector<int>& nums){
	TreeNode* root=new TreeNode(l,h);
	if(l==h){
		root->val=nums[l];
		return root;
	}
	int m=(l+h)/2;
	root->left=build(l,m,nums);
	root->right=build(m+1,h,nums);
	root->val=root->left->val+root->right->val;
	return root;
}
void push_down(TreeNode* root,int len){
	root->left->lazy+=root->lazy;
	root->right->lazy+=root->lazy;
	root->left->val+=root->lazy*(len-len/2);
	root->right->val+=root->lazy*(len/2);
	root->lazy=0;
}
void update(TreeNode* root,int l,int h,int v){
	int cl=root->low,ch=root->high;
	if(cl>h||ch<l) return;
	else if(l<=cl&&ch<=h){
		root->val+=(ch-cl+1)*v;
		if(root->left||root->right){
			root->lazy+=v;
		}
	}
	else{
		push_down(root,ch-cl+1);
		update(root->left,l,h,v);
		update(root->right,l,h,v);
		root->val=root->left->val+root->right->val;
	}
}
int query(TreeNode* root,int l,int h){
	int cl=root->low,ch=root->high;
	if(cl>h||ch<l) return 0;
	else if(l<=cl&&ch<=h) return root->val;
	else{
		push_down(root,ch-cl+1);
		return query(root->left,l,h)+query(root->right,l,h);
	}
}

void dfs(TreeNode* root){
	if(!root) return;
	cout<<root->val<<" ";
	dfs(root->left);
	dfs(root->right);
}
void bfs(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty()){
		int sz=q.size();
		for(int i=0;i<sz;i++){
			cout<<q.front()->val<<" ";
			if(q.front()->left) q.push(q.front()->left);
			if(q.front()->right) q.push(q.front()->right);
			q.pop();
		}
		cout<<endl;
	}
}
int main(){
	
}
