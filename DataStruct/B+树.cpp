#include<bits/stdc++.h>
using namespace std;
template<typename T,int m=4>
class BPlusTree{
	template<class U>
	struct TreeNode{
		bool isLeaf=true;
		TreeNode<T>* parent=nullptr;
		TreeNode<T>* next=nullptr;
		// 最多m-1个值
		vector<T> values;
		// 最多m个孩子
		vector<TreeNode<T>*> children;
		
		// 根节点构造
		TreeNode(T v,bool leaf=true):isLeaf(leaf){
			values.push_back(v);
		}
		// 分裂节点构造
		TreeNode(TreeNode<T>*& root,bool leaf,int l,int r,TreeNode<T>* next=nullptr,TreeNode<T>* parent=nullptr):isLeaf(leaf),next(next),parent(parent){
			for(int i=l;i<r;i++){
				values.push_back(root->values[i]);
			}
			if(root->isLeaf) return;
			for(int i=l;i<r;i++){
				root->children[i]->parent=this;
				children.push_back(root->children[i]);
			}
		}
		
		// 在当前节点中查询插入点位置
		int insertPos(T& val){
			if(values.empty()||val<=values[0]) return 0;
			int res=0;
			while(res<values.size()&&val> values[res]){
				res++;
			}
			return res;
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
			this->next=cur->next;
		}
	};
public:
	BPlusTree(){}
	BPlusTree(vector<T>& nums){
		for(auto& num:nums){
			insert(num);
		}
	}
	void insert(T val){
		insert(root,val);
	}
	void dfs(){
		auto f=[&](auto&& self,TreeNode<T>* r)->void{
			if(!r) return;
			for(int i=0;i< r->values.size();i++){
				if(i< r->children.size()) self(self,r->children[i]);
				cout<<r->values[i]<<" ";
			}
			if(!r->children.empty()) self(self,r->children[r->children.size()-1]);
		};
		
		f(f,root);
	}
	void lkshow(){
		TreeNode<T>* t=root;
		while(!t->children.empty()){
			TreeNode<T>* p=t;
			while(p){
				for(auto& val:p->values){
					cout<<val<<" ";
				}
				p=p->next;
			}
			t=t->children[0];
			cout<<endl;
		}
		while(t){
			for(auto& val:t->values){
				cout<<val<<" ";
			}
			t=t->next;
		}
		cout<<endl;
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
			int t=r->insertPos(val);
			if(t< r->values.size()&&r->values[t]==val) return true;
			r=r->children[t];
		}
		return false;
	}
	void erase(T val){
		erase(root,val);
	}
private:
	void insert(TreeNode<T>* cur,T val){
		auto f=[&](TreeNode<T>*& cur)->void{
			// 中位数节点
			T mid=cur->values[(m-1)/2];
			// 构造新节点会引起next指向cur的节点指针问题，所以在B+树中采用原地修改cur的方法
			while(cur->values.size()>(m+1)/2){
				cur->values.pop_back();
				if(!cur->children.empty()) cur->children.pop_back();
			}
			TreeNode<T>* r=new TreeNode<T>(cur,cur->isLeaf,(m+1)/2,m,cur->next,cur->parent);
			cur->next=r;
			
			// 根节点分裂
			if(!cur->parent){
				TreeNode<T>* new_r=new TreeNode<T>(mid,false);
				new_r->values.push_back(r->values.back());
				cur->parent=new_r;
				r->parent=new_r;
				new_r->children.push_back(cur);
				new_r->children.push_back(r);
				root=new_r;
				cur=root;
				return;
			}
			// 非根节点分裂
			TreeNode<T>* p=cur->parent;
			int t=p->insertPos(mid);
			
			p->values.insert(p->values.begin()+t,mid);
			p->children.insert(p->children.begin()+t+1,r);
			cur=p;
		};
		
		// 若当前节点是第一个插入节点
		if(!cur){
			cur=new TreeNode<T>(val);
			if(!root) root=cur;
			return;
		}
		int t=cur->insertPos(val);
		
		if(!cur->isLeaf){
			if(t==cur->values.size()){
				t--;
				cur->values[t]=val;
			}
			insert(cur->children[t],val);
		}
		else{
			cur->values.insert(cur->values.begin()+t,val);
			while(cur&&cur->values.size()==m){
				f(cur);
			}
		}
	}
	
	void erase(TreeNode<T>*& cur,T val,int pos=0){
		if(!cur) return;
		int t=cur->insertPos(val);
		if(cur->values[t]!=val){
			erase(cur->children[t],val,t);
		}
		else{
			if(cur->isLeaf){
				cur->values.erase(cur->values.begin()+t);
			}
			else{
				T new_val=getNext(cur->children[t+1]);
				cur->values[t]=new_val;
				erase(cur->children[t+1],new_val,t+1);	
			}
		}
		if(cur==root||cur->values.size()>=(m-1)/2) return;
		TreeNode<T>* p=cur->parent;
		// 右节点存在且有多余键值，找右节点要一个 孩子节点也要修改
		if(pos< p->children.size()-1&&p->children[pos+1]->values.size() >(m-1)/2){
			cur->values.push_back(p->values[pos]);
			p->values[pos]=p->children[pos+1]->values.front();
			p->children[pos+1]->values.erase(p->children[pos+1]->values.begin());
			
			if(!p->children[pos+1]->children.empty()){
				cur->children.push_back(p->children[pos+1]->children.front());
				p->children[pos+1]->children.erase(p->children[pos+1]->children.begin());
			}
			return;
		}
		// 左节点存在且有多余键值，找左节点要一个 孩子节点也要修改
		if(0<pos&&p->children[pos-1]->values.size() >(m-1)/2){
			cur->values.insert(cur->values.begin(),p->values[pos-1]);
			p->values[pos-1]=p->children[pos-1]->values.back();
			p->children[pos-1]->values.pop_back();
			
			if(!p->children[pos-1]->children.empty()){
				cur->children.insert(cur->children.begin(),p->children[pos-1]->children.back());
				p->children[pos-1]->children.pop_back();
			}
			return;
		}
		
		
		// 左节点存在且键值数为最小度，找左节点合并
		if(0<pos){
			p->children[pos-1]->values.push_back(p->values[pos-1]);
			p->values.erase(p->values.begin()+pos-1);
			p->children[pos-1]->combine(cur);
			
			p->children.erase(p->children.begin()+pos);
		}
		// 右节点存在且键值数为最小度，找右节点合并
		else{
			cur->values.push_back(p->values[pos]);
			p->values.erase(p->values.begin()+pos);
			cur->combine(p->children[pos+1]);
			
			p->children.erase(p->children.begin()+pos+1);
		}
		// 检查一下根节点
		if(cur->parent==root&&root->values.empty()){
			root=cur;
		}
	}
	T getNext(TreeNode<T>* cur){
		while(!cur->isLeaf){
			cur=cur->children[0];
		}
		return cur->values.front();
	}
	
	
	TreeNode<T> *root=nullptr;
};

int main(){
	string s="plokmijnuhbygvtfcrdxeszwaq";
	vector<char> v;
	for(auto& c:s){
		v.push_back(c);
	}
	BPlusTree<char,4> test(v);
	test.bfs();
}
