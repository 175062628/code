#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
	int val=0,low,high,lazy=0;
	TreeNode *left=nullptr,*right=nullptr;
	TreeNode(int l,int h):low(l),high(h){}
	TreeNode(TreeNode* l,TreeNode* r):left(l),right(r){}
};

class SegmentTree{
private:
	TreeNode* root;
	void push_down(TreeNode* r,int len){
		r->left->lazy+=r->lazy;
		r->right->lazy+=r->lazy;
		r->left->val+=r->lazy*(len-len/2);
		r->right->val+=r->lazy*(len/2);
		r->lazy=0;
	}
public:
	SegmentTree(vector<int>& nums){
		auto f=[](auto&& self,int l,int h,vector<int>& nums)->TreeNode*{
			TreeNode* root=new TreeNode(l,h);
			if(l==h){
				root->val=nums[l];
				return root;
			}
			int m=(l+h)/2;
			root->left=self(self,l,m,nums);
			root->right=self(self,m+1,h,nums);
			root->val=root->left->val+root->right->val;
			return root;
		};
		root=f(f,0,nums.size()-1,nums);
	}
	void update(int l,int h,int v){
		TreeNode *t=root;
		auto f=[this](auto&& self,TreeNode* r,int l,int h,int v)->void{
			int cl=r->low,ch=r->high;
			if(cl>h||ch<l) return;
			else if(l<=cl&&ch<=h){
				r->val+=(ch-cl+1)*v;
				if(r->left||r->right){
					r->lazy+=v;
				}
			}
			else{
				push_down(r,ch-cl+1);
				self(self,r->left,l,h,v);
				self(self,r->right,l,h,v);
				r->val=r->left->val+r->right->val;
			}
		};
		f(f,t,l,h,v);
	}
	int query(int l,int h){
		TreeNode *t=root;
		auto f=[this](auto&& self,TreeNode* r,int l,int h)->int{
			int cl=r->low,ch=r->high;
			if(cl>h||ch<l) return 0;
			else if(l<=cl&&ch<=h) return r->val;
			else{
				push_down(r,ch-cl+1);
				return self(self,r->left,l,h)+self(self,r->right,l,h);
			}
		};
		return f(f,t,l,h);
	}
	void show(){
		TreeNode *t=root;
		auto f=[](auto&& self,TreeNode* r)->void{
			if(!r) return;
			cout<<r->val<<" ";
			self(self,r->left);
			self(self,r->right);
		};
		f(f,t);
		cout<<endl;
	}
};

int main(){
	
}
