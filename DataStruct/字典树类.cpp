#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
	bool isWord=false;
	vector<TreeNode*> children=vector<TreeNode*>(26,nullptr);
	TreeNode(){}
	TreeNode(bool b):isWord(b){}
};
class Trie {
public:
	Trie(vector<string>& words){
		root=new TreeNode();
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
	}
	bool search(string s){
		TreeNode* t=root;
		for(int i=0;i<s.length();i++){
			if(!t->children[s[i]-'a']){
				return false;
			}
			t=t->children[s[i]-'a'];
		}
		return t->isWord;
	}
	void insert(string s){
		TreeNode* t=root;
		for(int i=0;i<s.length();i++){
			if(!t->children[s[i]-'a']){
				t->children[s[i]-'a']=new TreeNode();
			}
			t=t->children[s[i]-'a'];
		}
		t->isWord=true;
	}
	bool delet(string s){
		if(search(s)){
			TreeNode* t=root;
			for(int i=0;i<s.length();i++){
				t=t->children[s[i]-'a'];
			}
			t->isWord=false;
			return true;
		}
		return false;
	}
private:
	TreeNode* root;
};


int main(){
	
}
