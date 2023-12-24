#ifndef RB_TREE
#define RB_TREE

#include<bits/stdc++.h>
using namespace std;

#define RED 0
#define BLACK 1

template<typename T>
class RB_Tree{
	
	// U没啥用，只是为了声明
	template<typename U>
	struct TreeNode{
		T val;
		int color;
		TreeNode<T> *left=nullptr,*right=nullptr,*parent=nullptr;
		
		TreeNode(int c):color(c){}
		TreeNode(T v,int c):val(v),color(c){}
		TreeNode(T v,TreeNode* l=nullptr,TreeNode* r=nullptr,TreeNode* p=nullptr):val(v),color(RED),left(l),right(r),parent(p){}
		
		TreeNode<T>* grandparent(){
			if(!parent) return nullptr;
			return parent->parent;
		}
		TreeNode<T>* uncle(){
			if(!grandparent()) return nullptr;
			if(grandparent()->left==parent) return grandparent()->right;
			return grandparent()->left;
		}
		TreeNode<T>* sibling(){
			if(!parent) return nullptr;
			if(parent->left==this) return parent->right;
			return parent->left;
		}
		string outC(){
			return color==BLACK ? "BLACK":"RED";
		}
	};
public:
	RB_Tree(){}
	RB_Tree(vector<T> nums){
		for(auto& num:nums){
			insert(num);
		}
	}
	void insert(T val){
		insert(root,val);
	}
	void erase(T val){
		erase(root,val);
	}
	bool search(T val){
		auto f=[&](TreeNode<T>* r,T v)->bool{
			while(r!=nil){
				if(v==r->val) return true;
				if(v< r->val) r=r->left;
				else r=r->right;
			}
			return false;
		};
		return f(root,val);
	}
	void dfs(){
		auto f=[&](auto&& self,TreeNode<T>* r)->void{
			if(!r) cout<<"empty!"<<endl;
			if(r==nil||r==nullptr) return;
			self(self,r->left);
			cout<<r->val<<" "<<r->outC()<<endl;
			self(self,r->right);
		};
		
		f(f,root);
	}
private:
	/* 侯捷书版	
	 * case 1:	外侧插入，S为B	
	 *				G(B)                    P(B)
	 * 			   /    \      右旋		   /    \
	 * 			 P(R)   S(B)   ===>		  X(R)  G(R)
	 * 			/	\    |						/  \
	 * 		 X(R)    A   UN  				   A  S(B)
	 * 											    |
	 *											    UN
	 *
	 *  case 2:	内侧插入，S为B
	 * 				G(B)                    G(R)				    X(B)
	 * 			   /    \      左旋		   /    \	    右旋	   /    \
	 * 			  P(R)  S(B)   ===>		  X(B)  S(B)    ===>	  P(R)  G(R)
	 * 			 /  \	 |	    		 /		  |			     /		  \
	 * 			A  X(R)	 UN		    	P(R)     UN		    	A		  S(B)
	 * 								   /								   |	
	 * 								  A									   UN
	 * 
	 *  ********与实操版不同*******
	 *  case 3:	外侧插入，S为R，GG为B
	 * 				G(B)                    P(R)
	 * 			   /    \      右旋		   /    \
	 * 			  P(R)  S(R)   ===>		  X(B)  G(B)
	 * 			 /	 \	 |						/  \
	 * 			X(R)  A  UN 				   A	S(R)
	 * 												 |
	 * 											     UN	
	 * 
	 *  case 4：外侧插入，S为R，GG为R
	 * 				  GGG(B)				     GGG(B)						 GG(B)
	 * 				 /		\				    /	   \					 /	  \
	 * 				GG(R)	 Q(B)		  	   GG(R)    Q(B)			  P(R)	   GGG(R)
	 * 			   /     \	   |		      /     \	  |				  /	 \      /    \
	 * 			  G(B)    T(B) UN  右旋      P(R)	 T(B) UN    右旋	X(B) G(B)  T(B)  Q(B)	
	 *			 /    \     |      ===>      /  \      |        ===>	     /  \   |	  |
	 * 		   P(R)   S(R) UN			    X(B) G(B)  UN			        A S(R)  UN	  UN
	 *  	   / \	   | 	   			         /	\						    |
	 * 		 X(R) A	   UN	 			        A    S(R)				        UN
	 * 											      |
	 * 											      UN
	 * *****************************************************************************************
	 * 本人修改版：
	 * 	case 3 & case 4合并：外侧插入，S为R，向上递归P节点
	 * 
	 * 	case 5：内侧插入，S为R，向上递归X节点
	 *  			  GGG(B)				     GGG(B)						 GGG(B)
	 * 				 /		\				    /	   \					 /	  \
	 * 				GG(R)	 Q(B)		  	   GG(R)    Q(B)			  GG(R)	   Q(B)
	 * 			   /     \	   |		      /     \	  |				  /	 \     
	 * 			  G(B)    T(B) UN  左旋      G(B)	 T(B) UN    右旋	X(R) T(B) 	
	 *			 /    \     |      ===>      /  \      |        ===>	/  \     
	 * 		   P(R)   S(R) UN			    X(R) S(R)  UN			   P(B) G(B)
	 *  	   / \	   | 	   			    /     						      \
	 * 		  A	 X(R)  UN	 			   P(B)     				          S(R)
	 * 											      
	 * 											      
	 */
	void insertCheck1(TreeNode<T>*& cur){
		// 没有父节点的情况
		if(!cur->parent){
			cur->color=BLACK;
			root=cur;
			return;
		}
		// 父节点为黑则直接插入
		if(cur->parent->color==BLACK) return;
		// case 1 && case 2 && case 3
		if(cur->uncle()->color==BLACK){
			// case 1
			if(cur->grandparent()->left==cur->parent&&cur->parent->left==cur){	// LL
				cur->parent->color=BLACK;
				cur->grandparent()->color=RED;
				RotateR(cur->parent);
			}
			else if(cur->grandparent()->right==cur->parent&&cur->parent->right==cur){	// RR
				cur->parent->color=BLACK;
				cur->grandparent()->color=RED;
				RotateL(cur->parent);
			}
			// case 2
			else if(cur->grandparent()->left==cur->parent&&cur->parent->right==cur){	// LR
				cur->color=BLACK;
				cur->grandparent()->color=RED;
				RotateL(cur);
				RotateR(cur);
			}
			else if(cur->grandparent()->right==cur->parent&&cur->parent->left==cur){	// RL
				cur->color=BLACK;
				cur->grandparent()->color=RED;
				RotateR(cur);
				RotateL(cur);
			}
		}
		else{
			// case 3 && case 4
			if(cur->grandparent()->left==cur->parent&&cur->parent->left==cur){	// LL
				cur->color=BLACK;
				RotateR(cur->parent);
				insertCheck1(cur->parent);
			}
			else if(cur->grandparent()->right==cur->parent&&cur->parent->right==cur){	// RR
				cur->color=BLACK;
				RotateL(cur->parent);
				insertCheck1(cur->parent);
			}
			// case 5
			else if(cur->grandparent()->left==cur->parent&&cur->parent->right==cur){	// LR
				cur->parent->color=BLACK;
				RotateL(cur);
				RotateR(cur);
				insertCheck1(cur);
			}
			else if(cur->grandparent()->right==cur->parent&&cur->parent->left==cur){	// RL
				cur->parent->color=BLACK;
				RotateR(cur);
				RotateL(cur);
				insertCheck1(cur);
			}
		}
	}
	
	/*  实操版
	 *  case 1：父节点为nullptr
	 * 			把插入节点变为B，根节点变为当前节点
	 *
	 *  case 2：父节点为B
	 * 			直接插入
	 * 
	 *  ***********************************************
	 *  * 以下情况若没有叔叔节点，则把nil看做叔叔节点 *
	 *  ***********************************************
	 * 
	 *  case 3：父节点为R，叔叔节点为R
	 * 			父节点为B，叔叔节点为B，祖父节点变为R，递归检查祖父节点(相当于把祖父节点当做新插入的节点)
	 * 
	 *  case 4：父节点为R，叔叔节点为B，外侧插入(LL,RR)
	 *				G(B)                    P(B)
	 * 			   /    \      右旋		   /    \
	 * 			 P(R)   S(B)   ===>		  X(R)  G(R)
	 * 			/	\    |						/  \
	 * 		 X(R)    A   UN  				   A  S(B)
	 * 											    |
	 *											    UN
	 *
	 *  case 5：父节点为R，叔叔节点为B，内侧插入(LR,RL)
	 * 				G(B)                    G(R)				    X(B)
	 * 			   /    \      左旋		   /    \	    右旋	   /    \
	 * 			  P(R)  S(B)   ===>		  X(B)  S(B)    ===>	  P(R)  G(R)
	 * 			 /  \	 |	    		 /		  |			     /		  \
	 * 			A  X(R)	 UN		    	P(R)     UN		    	A		  S(B)
	 * 								   /								   |	
	 * 								  A									   UN
	 * 
	 */
	void insertCheck2(TreeNode<T>*& cur){
		// case 1
		if(!cur->parent){
			cur->color=BLACK;
			root=cur;
			return;
		}
		// case 2
		if(cur->parent->color==BLACK) return;
		// case 3
		if(cur->uncle()->color==RED){
			cur->parent->color=BLACK;
			cur->uncle()->color=BLACK;
			cur->grandparent()->color=RED;
			insertCheck2(cur->parent->parent); // 这里不用grandparent是因为inseCheck传入的是指针的引用
		}
		else{
			// case 4
			if(cur->grandparent()->left==cur->parent&&cur->parent->left==cur){ // R
				cur->parent->color=BLACK;
				cur->grandparent()->color=RED;
				RotateR(cur->parent);
			}
			else if(cur->grandparent()->right==cur->parent&&cur->parent->right==cur){ // L
				cur->parent->color=BLACK;
				cur->grandparent()->color=RED;
				RotateL(cur->parent);
			}
			// case 5
			else if(cur->grandparent()->left==cur->parent&&cur->parent->right==cur){ // LR
				cur->color=BLACK;
				cur->grandparent()->color=RED;
				RotateL(cur);
				RotateR(cur);
			}
			else if(cur->grandparent()->right==cur->parent&&cur->parent->left==cur){ // RL
				cur->color=BLACK;
				cur->grandparent()->color=RED;
				RotateR(cur);
				RotateL(cur);
			}
		}
	}
	void insert(TreeNode<T>*& cur,T val){
		if(!cur){
			TreeNode<T>* t=new TreeNode<T>(val,nil,nil);
			insertCheck2(t);
			return;
		}
		if(val<= cur->val){
			if(cur->left!=nil){
				insert(cur->left,val);
			}
			else{
				TreeNode<T>* t=new TreeNode<T>(val,nil,nil,cur);
				cur->left=t;
				insertCheck2(t);
			}
		}
		else{
			if(cur->right!=nil){
				insert(cur->right,val);
			}
			else{
				TreeNode<T>* t=new TreeNode<T>(val,nil,nil,cur);
				cur->right=t;
				insertCheck2(t);
			}
		}
	}
	
	/*	case 1：待删除节点有两个孩子节点
	 *			找到其前驱(左子树最大值)或后继(右子树最小值)，把其值修改为前驱或后继的值，然后删除其前驱或后继。
	 *
	 *  ******************************************
	 *  * 以下情况待删除节点都至多有一个孩子节点 *
	 *  ******************************************
	 * 
	 *	case 2：待删除节点是R
	 *			把父节点的指针指向孩子节点，删除该节点
	 *
	 *	case 3：待删除节点是B，其孩子节点是R
	 *			把父节点的指针指向孩子节点，孩子节点修改为B，删除该节点
	 *
	 *	case 4：待删除节点是B，其孩子节点是B
	 *		先让孩子节点替换待删除的节点，然后分类讨论
	 *		NEW为替换上的节点，P为父节点，S为兄弟节点，SL是兄弟节点的左节点，SR是兄弟节点的右节点
	 *
	 *		case 1：孩子节点作为新的根节点
	 *				结束
	 *
	 *		case 2：兄弟节点是R，其余都是B
	 * 					P(B)                        S(B)
	 * 				   /x-1 \       左旋变色	   /    \x
	 * 			  (x)NEW(B)  S(R)   ========>	 P(R)  SR(B)
	 *				/ \     /x \x             x-1/  \x   
	 *			   P  Q  SL(B) SR(B)	 	 NEW(B) SL(B)
	 *				修改完后，仍需调整，转case 4/5/6
	 *  
	 *		case 3：所有节点都是B
	 *    			    		T						  T
	 *    			      	  x/ \x						x/ \x
	 *  			    	P(B)  TL	  变色		  P(B)  TL
	 *   	    		x+1/   \x+1       ====>	    x+1/ \x
	 *         	   (x+2)NEW(B) S(B)			  	  NEW(B) S(R)	
	 *              	/\    /x+2 \x+2			  /\	/x+1 \x+1
	 *	               P  Q  SL(B) SR(B)		 P  Q  SL(B) SR(B)(x+2)
	 * 				修改完后，以P为根的子树黑色节点数比T的另一子树路径上黑色节点个数少1，仍需调整，转case 1
	 * 
	 * 		case 4：父节点是R，其余节点是B
	 * 				P变B，S变R，
	 * 					P(R)                    P(B)
	 * 				   /    \      变色	  	   /    \
	 * 			  	NEW(B)  S(B)   ====>	NEW(B)  S(R)
	 *			   	/ \      /  \            / \	/  \ 
	 *			   	P  Q  SL(B) SR(B)	 	P  Q SL(B) SR(B)
	 * 				结束
	 * 
	 * 		case 5：SL和SR中的内侧点是R(RL,LR)，其余为B
	 * 					T                		T
	 * 					 \          右旋变色	 \
	 * 					 S(B)       =======>	 SL(B)
	 * 					/	\  				  	/  \
	 * 				 SL(R)   SR(B)  		 	A  S(R)
	 * 				/	\	/	\					/  \		
	 * 			   A	 B C     D			   	   B   SR(B)
	 * 													/ \
	 * 											   	   C   D
	 * 				旋转并交换颜色，转case 6
	 * 
	 * 		case 6：SL和SR中的外侧点是R
	 * 					P(ALL)						S(ALL)
	 *				   / \ 			左旋变色		/  \
	 * 			   NEW(B) S(B)		=======>	  P(B) SR(B)
	 * 						\					  /
	 * 						SR(R)				NEW(B)
	 * 				结束
	 */
	// cur是替换节点
	void eraseCase(TreeNode<T>*& cur){
		// case 1
		if(!cur->parent){
			root=cur;
			return;
		}
		TreeNode<T> *p=cur->parent,*s=cur->sibling(),*sl=s->left,*sr=s->right;
		// case 2
		if(p->color==BLACK&&s->color==RED&&sl->color==BLACK&&sr->color==BLACK){
			p->color=RED;
			s->color=BLACK;
			if(p->left==cur){
				RotateR(s);
			}
			else{
				RotateL(s);
			}
		}
		// case 3
		else if(p->color==BLACK&&s->color==BLACK&&sl->color==BLACK&&sr->color==BLACK){
			s->color=RED;
			eraseCase(p);
		}
		// case 4
		else if(p->color==RED&&s->color==RED&&sl->color==BLACK&&sr->color==BLACK){
			p->color=BLACK;
			s->color=RED;
		}
		// case 5 && case 6
		else{
			// case 5
			if(s->color==BLACK){
				if(s->parent->left==s&&sr->color==RED&&sl->color==BLACK){	// LR
					sr->color=BLACK;
					s->color=RED;
					RotateL(sr);
				}
				else if(s->parent->right==s&&sl->color==RED&&sr->color==BLACK){ // RL
					sl->color=BLACK;
					s->color=RED;
					RotateR(sl);
				}
			}
			// case 6
			TreeNode<T> *p=cur->parent,*s=cur->sibling(),*sl=s->left,*sr=s->right;
			s->color=p->color;
			p->color=BLACK;
			if(s==p->left){	// LL	
				sl->color=BLACK;
				RotateR(s);
			}
			else if(s==p->right){ // RR
				sr->color=BLACK;
				RotateL(s);
			}
		}
	}
	// cur是待删除节点 只考虑至多一个子节点的情况
	void eraseHelp(TreeNode<T>* cur){ // 引用传递就会报错，原因在于引用传递会在原地址上修改，即parent->child==cur
		TreeNode<T>* child=cur->left!=nil?cur->left:cur->right;
		if(!cur->parent&&cur->left==nil&&cur->right==nil){
			delete cur;
			root=nullptr;
			return;
		}
		// case 1
		if(!cur->parent){
			child->color=BLACK;
			child->parent=nullptr;
			delete cur;
			root=child;
			return;
		}
		// case 2 && case 3 && case 4
		if(cur->parent->left==cur){
			cur->parent->left=child;
		}
		else{
			cout<<cur<<endl;
			cout<<&cur<<endl;
			cout<<&cur->parent->right<<endl;
			
			cur->parent->right=child;	// 引用传递修改后父节点信息为空，会报错
			
			
			cout<<cur->val<<" "<<cur->outC()<<endl;
			
		}
		child->parent=cur->parent;
		if(cur->color==BLACK){
			delete cur;
			// case 3
			if(child->color==RED) child->color=BLACK;
			// case 4
			else eraseCase(child);
		}
	}
	void erase(TreeNode<T>*& cur,T val){
		if(cur==nil) return;
		if(val< cur->val){
			erase(cur->left,val);
		}
		else if(val> cur->val){
			erase(cur->right,val);
		}
		else{
			if(cur->right==nil){
				eraseHelp(cur);
				return;
			}
			TreeNode<T>* next=getMin(cur->right);
			cur->val=next->val;
			eraseHelp(next);
		}
	}
	
	// cur是旋转完的根节点
	void RotateR(TreeNode<T>*& cur){
		TreeNode<T> *parent=cur->parent,*grandparent=cur->grandparent(),*right=cur->right;
		// 修改右节点
		if(right!=nil) right->parent=parent;
		parent->left=right;
		// 修改cur节点
		cur->right=parent;
		parent->parent=cur;
		if(root==parent) root=cur;
		cur->parent=grandparent;
		// 修改grandparent节点
		if(grandparent){
			if(grandparent->left==parent) grandparent->left=cur;
			else grandparent->right=cur;
		}
	}
	void RotateL(TreeNode<T>*& cur){
		TreeNode<T> *parent=cur->parent,*grandparent=cur->grandparent(),*left=cur->left;
		// 修改left
		if(left!=nil) left->parent=parent;
		parent->right=left;
		// 修改cur
		cur->left=parent;
		parent->parent=cur;
		if(parent==root) root=cur;
		cur->parent=grandparent;
		// 修改grandparent
		if(grandparent){
			if(grandparent->left==parent) grandparent->left=cur;
			else grandparent->right=cur;
		}
	} 
	
	TreeNode<T>* getMin(TreeNode<T>* r){
		while(r->left!=nil){
			r=r->left;
		}
		return r;
	}	
	TreeNode<T>* getMax(TreeNode<T>* r){
		while(r->right!=nil){
			r=r->right;
		}
		return r;
	}
	
	TreeNode<T> *root=nullptr,*nil=new TreeNode<T>(BLACK);
};


#endif
