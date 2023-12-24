#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
	int val;
	int height=0;
	TreeNode *left=nullptr,*right=nullptr;
	TreeNode(int v,TreeNode* l=nullptr,TreeNode* r=nullptr):val(v),height(1),left(l),right(r){}
};
class AVLTree{
public:
	AVLTree(vector<int>& nums){
		for(auto& num:nums) insert(num);
	}
	void insert(int v){
		auto f=[&](auto&& self,TreeNode*& r,int val)->TreeNode*{
			if(!r){
				r=new TreeNode(val);
			}
			// 右插入
			else if(val > r->val){
				r->right=self(self,r->right,val);
				// R
				if((r->right ? r->right->height:0) - (r->left ? r->left->height:0) >1){
					// R
					if (val > r->right->val) r=rotateRR(r);
					// L
					else r=rotateRL(r);
				}
			}
			// 左插入
			else{
				r->left=self(self,r->left,val);
				// L
			    if((r->left ? r->left->height:0) - (r->right ? r->right->height:0) >1){
				    // L
				    if(val < r->left->val) r=rotateLL(r);
				    // R
				    else r=rotateLR(r);
			    }
			}
			r->height=max(r->left ? r->left->height:0,r->right ? r->right->height:0)+1;
			return r;
		};
		
		f(f,root,v);
	}
	void erase(int v){
		auto getMax=[](TreeNode* r)->TreeNode*{
			if(!r) return nullptr;
			while(r->right){
				r=r->right;
			}
			return r;
		};
		
		auto getMin=[](TreeNode* r)->TreeNode*{
			if(!r) return nullptr;
			while(r->left){
				r=r->left;
			}
			return r;
		};
		
		auto f=[&](auto&& self,TreeNode*& r,int val)->TreeNode*{
			if(!r) return nullptr;
			// 左删除
			if (val < r->val){
				r->left=self(self,r->left,val);
				// R
				if((r->right ? r->right->height:0) - (r->left ? r->left->height:0) >1){
					// L
					if((r->right->left ? r->right->left->height:0) > (r->right->right ? r->right->right->height:0)) r=rotateRL(r);
					// R
					else r=rotateRR(r);
				}
			}
			// 右删除
			else if (val > r->val){
				r->right=self(self,r->right,val);
				// L
				if((r->left ? r->left->height:0) - (r->right ? r->right->height:0) >1){
					// R
					if((r->left->right ? r->left->right->height:0) > (r->left->left ? r->left->left->height:0)) r=rotateLR(r);
					// L
					else r=rotateLL(r);
				}
			}
			else{
				// 左右孩子都有，找最大(小)值,替换值，然后旋转
				if(r->left&&r->right){
					if(r->left->height > r->right->height){
						TreeNode* max=getMax(r->left);
						r->val=max->val;
						r->left=self(self,r->left,max->val);
						delete max;
					}
					else{
						TreeNode* min=getMin(r->right);
						r->val=min->val;
						r->right=self(self,r->right,min->val);
						delete min;
					}
				}
				else{
					TreeNode* t=r;
					r=r->left ? r->left:r->right;
					delete t;
				}
			}
			return r;
		};	
		
		f(f,root,v);
	}	
	TreeNode* search(int v){
		while(root){
			if(v==root->val) return root;
			if(v< root->val) root=root->left;
			root=root->right;
		}
		return nullptr;
	}
private:
	/* LL：左子树的左边失去平衡(左单旋转)
	 *        r               t     
	 *       / \             / \
	 *      t   z   ===>    x   r
	 *     / \             /   / \
	 *    x   y           num y   z
	 *   / 
	 *  num          
	 */	
	TreeNode* rotateLL(TreeNode*& r){
		TreeNode* t=r->left;
		r->left=t->right;
		t->right=r;
		r->height=max(r->left ? r->left->height:0,r->right ? r->right->height:0)+1;
		t->height=max(t->left ? t->left->height:0,t->right ? t->right->height:0)+1;
		return t;
	}
	
	/* RR：右子树的右边失去平衡(右单旋转)
	 *       r              t     
	 *      / \            / \
	 *     x   t   ===>   r   z
	 *        / \        / \   \
	 *       y   z      x   y  num
	 *            \
	 *            num
	 */
	TreeNode* rotateRR(TreeNode*& r){
		TreeNode* t=r->right;
		r->right=t->left;
		t->left=r;
		r->height=max(r->left ? r->left->height:0,r->right ? r->right->height:0)+1;
		t->height=max(t->left ? t->left->height:0,t->right ? t->right->height:0)+1;
		return t;
	}
	
	/* LR：左子树的右边失去平衡(左双旋转)
	 *       r                  r               rlr
	 *      / \      RR        / \     LL      /   \
	 *     rl  D    ===>     rlr  D   ===>    rl    r
	 *    /  \              /   \            / \   / \
	 *   A   rlr           rl    C          A   B C   D
	 *       /  \         /  \    \                \
	 *      B    C       A    B   num              num
	 *            \
	 *            num
	 */
	TreeNode* rotateLR(TreeNode*& r){
		r->left=rotateRR(r->left);
		return rotateLL(r);
	}
	
	/* RL：右子树的左边失去平衡(右双旋转)
	 *       r                r                   rrl
	 *      / \       LL     / \          RR     /   \
	 *     A   rr    ===>   A  rrl       ===>   r     rr
	 *        /  \            /   \            / \   /  \
	 *       rrl  D          B     rr         A   B C    D
	 *      /   \           /     /  \           /
	 *     B     C        num    C    D        num
	 *    /
	 *  num
	 */
	TreeNode* rotateRL(TreeNode*& r){
		r->right=rotateLL(r->right);
		return rotateRR(r);
	}

	TreeNode* root=nullptr;
};

int main(){
	
}
