#include<bits/stdc++.h>
using namespace std;
// 3阶B树还有点问题
// B树的阶 每个节点最多m-1个键值
template<typename T,int m=4>
class BTree{
	template<class U>
	struct TreeNode{
		bool isLeaf=true;
		TreeNode<T>* parent=nullptr;
		// 最多m-1个值
		vector<T> values;
		// 最多m个孩子
		vector<TreeNode<T>*> children;
		
		TreeNode():children(m,nullptr){}
		// 根节点构造
		TreeNode(T v,bool leaf=true):children(m,nullptr),isLeaf(leaf){
			values.push_back(v);
		}
		// 分裂节点构造
		TreeNode(TreeNode<T>*& root,bool leaf,int l,int r,TreeNode<T>* p=nullptr):children(m,nullptr),isLeaf(leaf),parent(p){
			for(int i=l;i<r;i++){
				values.push_back(root->values[i]);
				children[i-l]=root->children[i];
			}
			children[r-l]=root->children[r];
			
			for(auto& child:children){
				if(child){
					child->parent=this;
				}
			}
		}
		
		// 在当前节点中查询插入点位置
		int insertValue(T& val){
			if(values.empty()||val<=values[0]) return 0;
			int res=0;
			while(res<values.size()&&val> values[res]){
				res++;
			}
			return res;
		}
		void insertChild(TreeNode<T>* cur,int t){
			for(int i=m-1;i>t;i--){
				children[i]=children[i-1];
			}
			children[t]=cur;
		}
		
		void show(){
			for(auto& val:values){
				cout<<val<<" ";
			}
		}
		void combine(TreeNode<T>*& cur){
			for(auto& x:cur->values){
				values.push_back(x);
			}
		}
	};
public:
	BTree(){}
	BTree(vector<T>& nums){
		for(auto& num:nums){
			insert(num);
		}
	}
	void insert(T val){
		insert2(root,val);
		//root->show();
	}
	void dfs(){
		auto f=[&](auto&& self,TreeNode<T>*& r)->void{
			if(!r) return;
			for(int i=0;i< r->values.size();i++){
				self(self,r->children[i]);
				cout<<r->values[i]<<" ";
			}
			self(self,r->children[r->values.size()]);
		};
		
		f(f,root);
	}
	void bfs(){
		queue<TreeNode<T>*> q;
		q.push(root);
		while(!q.empty()){
			int sz=q.size();
			for(int i=0;i<sz;i++){
				q.front()->show();
				cout<<" | ";
				for(auto& p:q.front()->children){
					if(p) q.push(p);
				}
				q.pop();
			}
			cout<<endl;
		}
	}
	bool search(T val){
		TreeNode<T>* r=root;
		while(r){
			int t=r->insertValue(val);
			if(t< r->values.size()&&r->values[t]==val) return true;
			r=r->children[t];
		}
		return false;
	}
	void erase(T val){
		erase(root,val);
	}
private:
	// 先判断填满，再添加(路径上有满节点就先分裂  知乎/算法导论)
	// 算法导论指出 B树除根节点外的所有节点，最小度为t-1，最大度为2t-1
	// 故根据算法导论，本人有个推论，B树只能为偶数阶(但实操的时候并不是如此)
	void insert1(TreeNode<T>* cur,T val){
		// 分裂函数，在insert1和insert2中对r节点的构造略有不同 具体不同见下文split
		auto f=[&](TreeNode<T>*& cur)->void{
			// 中位数节点
			T mid=cur->values[(m-1)/2];
			TreeNode<T>* l=new TreeNode<T>(cur,cur->isLeaf,0,(m-1)/2,cur->parent);
			TreeNode<T>* r= m==3&&cur->children[2] ? cur->children[2]:new TreeNode<T>(cur,cur->isLeaf,(m+1)/2,m-1,cur->parent);
			//TreeNode<T>* r=new TreeNode<T>(cur,cur->isLeaf,(m+1)/2,m-1,cur->parent);
			
			// 根节点分裂
			if(!cur->parent){
				TreeNode<T>* new_r=new TreeNode<T>(mid,false);
				l->parent=new_r;
				r->parent=new_r;
				new_r->children[0]=l;
				new_r->children[1]=r;
				root=new_r;
				cur=root;
				return;
			}
			// 非根节点分裂
			TreeNode<T>* p=cur->parent;
			int t=p->insertValue(mid);
			
			p->values.insert(p->values.begin()+t,mid);
			p->children[t]=l;
			p->insertChild(r,t+1);
			cur=p;
		};
		
		// 若当前节点是第一个插入节点
		if(!cur){
			cur=new TreeNode<T>(val);
			if(!root) root=cur;
			return;
		}
		// 若当前节点已满，则分裂
		if(cur->values.size()==m-1){
			f(cur);
		}
		int t=cur->insertValue(val);
		if(!cur->isLeaf) insert1(cur->children[t],val);
		else cur->values.insert(cur->values.begin()+t,val);
	}
	// 先添加，再判断填满(先找到待插入节点，再判断插入后是否分裂  数据结构：C++实现(第2版)/维基百科)
	void insert2(TreeNode<T>* cur,T val){
		// 分裂函数，在insert1和insert2中对r节点的构造略有不同 具体不同见下文split
		auto f=[&](TreeNode<T>*& cur)->void{
			// 中位数节点
			T mid=cur->values[(m-1)/2];
			TreeNode<T>* l=new TreeNode<T>(cur,cur->isLeaf,0,(m-1)/2,cur->parent);
			TreeNode<T>* r=new TreeNode<T>(cur,cur->isLeaf,(m+1)/2,m-1,cur->parent);
			
			// 根节点分裂
			if(!cur->parent){
				TreeNode<T>* new_r=new TreeNode<T>(mid,false);
				l->parent=new_r;
				r->parent=new_r;
				new_r->children[0]=l;
				new_r->children[1]=r;
				root=new_r;
				cur=root;
				return;
			}
			// 非根节点分裂
			TreeNode<T>* p=cur->parent;
			int t=p->insertValue(mid);
			
			p->values.insert(p->values.begin()+t,mid);
			p->children[t]=l;
			p->insertChild(r,t+1);
			cur=p;
		};
		
		// 若当前节点是第一个插入节点
		if(!cur){
			cur=new TreeNode<T>(val);
			if(!root) root=cur;
			return;
		}
		int t=cur->insertValue(val);
		if(!cur->isLeaf) insert2(cur->children[t],val);
		else{
			stack<TreeNode<T>*> st;
			while(cur&&cur->values.size()==m-1){
				st.push(cur);
				cur=cur->parent;
			}
			while(!st.empty()){
				cur=st.top();
				f(cur);
				st.pop();
			}
			if(cur->isLeaf) cur->values.insert(cur->values.begin()+t,val);
			else insert2(cur,val);
		}
	}
	// 分裂函数 cur是待分裂节点
	void split(TreeNode<T>*& cur){
		// 中位数节点
		int mid=cur->values[(m-1)/2];
		TreeNode<T>* l=new TreeNode<T>(cur,cur->isLeaf,0,(m-1)/2,cur->parent);
		// insert1()的分裂构造
		// 特判m==3
		// 当m==3且children[2]为nullptr时，构造一个新的TreeNode
		TreeNode<T>* r= m==3&&cur->children[2] ? cur->children[2]:new TreeNode<T>(cur,cur->isLeaf,(m+1)/2,m-1,cur->parent);
		
		// insert2()的分裂构造
		//TreeNode<T>* r=new TreeNode<T>(cur,cur->isLeaf,(m+1)/2,m-1,cur->parent);
		
		// 根节点分裂
		if(!cur->parent){
			TreeNode<T>* new_r=new TreeNode<T>(mid,false);
			l->parent=new_r;
			r->parent=new_r;
			new_r->children[0]=l;
			new_r->children[1]=r;
			root=new_r;
			cur=root;
			return;
		}
		// 非根节点分裂
		TreeNode<T>* p=cur->parent;
		int t=p->insertValue(mid);
		
		p->values.insert(p->values.begin()+t,mid);
		p->children[t]=l;
		p->insertChild(r,t+1);
		cur=p;
	}
	
	
	void erase(TreeNode<T>*& cur,T val,int pos=0){
		if(!cur) return;
		int t=cur->insertValue(val);
		if(cur->values[t]!=val){
			erase(cur->children[t],val,t);
		}
		else{
			if(cur->isLeaf){
				cur->values.erase(cur->values.begin()+t);
				if(cur->values.size()>=(m-1)/2) return;
				TreeNode<T>* p=cur->parent;
				// 右节点存在且有多余键值，找右节点要一个
				if(0<=pos&&pos<m-2 &&p->children[pos+1]&&p->children[pos+1]->values.size() >(m-1)/2){
					insert2(cur,p->values[pos]);
					p->values[pos]=p->children[pos+1]->values[0];
					erase(p->children[pos+1],p->children[pos+1]->values[0]);
					return;
				}
				// 左节点存在且有多余键值，找左节点要一个
				if(0<pos&&pos<m-1 &&p->children[pos-1]&&p->children[pos-1]->values.size() >(m-1)/2){
					insert2(cur,p->values[pos-1]);
					p->values[pos-1]=p->children[pos-1]->values.back();
					erase(p->children[pos-1],p->children[pos-1]->values.back());
					return;
				}
				
				// 左节点存在且键值数为最小度，找左节点合并
				if(0<pos&&pos<m-1&&p->children[pos-1]){
					p->children[pos-1]->values.push_back(p->values[pos-1]);
					p->children[pos-1]->combine(cur);
					T div=p->children[pos-1]->values.back();
					p->children[pos-1]->values.pop_back();
					p->values[pos-1]=div;
					p->children[pos]=nullptr;
					return;
				}
				// 右节点存在且键值数为最小度，找右节点合并
				if(0<=pos&&pos<m-2&&p->children[pos+1]){
					cur->values.push_back(p->values[pos]);
					cur->combine(p->children[pos+1]);
					T div=cur->values.back();
					cur->values.pop_back();
					p->values[pos]=div;
					p->children[pos+1]=nullptr;
					return;
				}
			}
			else{
				cur->values[t]=getNext(cur->children[t+1]);
			}
		}
	}
	T getNext(TreeNode<T>* cur){
		while(!cur->isLeaf){
			cur=cur->children[0];
		}
		T res=cur->values.back();
		erase(cur,res);
		return res;
	}
	
	
	TreeNode<T> *root=nullptr;
};

int main(){
	string s="plokmijnuhbygvtfcrdxeszwaq";
	vector<char> v;
	for(auto& c:s){
		v.push_back(c);
	}
	BTree<char,5> test(v);
	test.bfs();
	test.erase('h');
	test.dfs();
}
