#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
	bool isWord=false;
	vector<TreeNode*> children=vector<TreeNode*>(26,nullptr);
	TreeNode(){}
	TreeNode(bool b):isWord(b){}
};
TreeNode* build(vector<string>& words){
	TreeNode* root=new TreeNode();
	for(auto& word:words){
		TreeNode* t=root;
		for(int i=0;i<word.length();i++){
			if(!t->children[word[i]-'a']){
				t->children[word[i]-'a']=new TreeNode();
			}
			t=t->children[word[i]-'a'];
		}
		t->isWord=true;
	}
	return root;
}
bool search(TreeNode* root,string s){
	for(int i=0;i<s.length();i++){
		if(!root->children[s[i]-'a']){
			return false;
		}
		root=root->children[s[i]-'a'];
	}
	return root->isWord;
}
void insert(TreeNode* root,string s){
	for(int i=0;i<s.length();i++){
		if(!root->children[s[i]-'a']){
			root->children[s[i]-'a']=new TreeNode();
		}
		root=root->children[s[i]-'a'];
	}
	root->isWord=true;
}
bool delet(TreeNode* root,string s){
	if(search(root,s)){
		for(int i=0;i<s.length();i++){
			root=root->children[s[i]-'a'];
		}
		root->isWord=false;
		return true;
	}
	return false;
}

int main(){

}
