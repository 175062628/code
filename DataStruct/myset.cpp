#include<bits/stdc++.h>
#include "../head/rb_tree.h"
using namespace std;
template<typename T>
class myset{
public:
	myset(){}
	myset(vector<T> nums){	
		tree=RB_Tree(nums);
	}
	void insert(T val){
		if(tree.search(val)) return;
		tree.insert(val);
	}
	void erase(T val){
		tree.erase(val);
	}
	bool search(T val){
		return tree.search(val);
	}
private:
	RB_Tree<T> tree;
};

int main(){
	vector<double> nums={2.3,6.5,8.2,1.6,9.3,5.6,4.7};
	myset<double> s(nums);
	cout<<s.search(2.3)<<endl;
	s.erase(2.3);
	cout<<s.search(2.3)<<endl;
}
