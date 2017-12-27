#include<iostream>
using namespace std;
class Node
{
	public:
		int val;
		Node* left;
		Node* right;
};

class BinarySearchTree
{
	public:
		Node* root;
		BinarySearchTree(int* array,int n)
		{
			Node* tmp=new Node(); //必须申请新的空间，否则等函数一结束，新创建的结点就会被释放，root就会成为野指针 
			tmp->val=array[0];
			root=tmp;
			for(int i=1; i<n; i++)
				insert(array[i]);
		}

		void insert(int e)
		{
			Node* p=root;
			Node* parent=NULL;//parent就是要插入结点的父结点
			while(p!=NULL)
			{
				//	cout<<p->val<<" ";
				if(e>p->val)
				{
					parent=p;
					p=p->right;
				}
				else
				{
					parent=p;
					p=p->left;
				}
			}
			if(e>parent->val)
			{
				Node* tmp=new Node();
				tmp->val=e;
				parent->right=tmp;
			}
			else
			{
				Node* tmp=new Node();
				tmp->val=e;
				parent->left=tmp;
			}
		}

		bool searchTree(int e)
		{
			Node* p=search(e,root);
			if(p!=NULL)
			{
				cout<<"找到了"<<p->val<<"\n";
				return true;
			}
			else
			{
				cout<<"没找到"<<e<<"\n";
				return false;
			}

		}

		Node* search(int e,Node* p)
		{
			if(p==NULL)
				return p;

			if(p->val==e)
				return p;
			else
			{
				if(e>p->val)
					return search(e,p->right); //这个也要加return 抛给上一层 
				else
					return search(e,p->left);
			}
		}

		void printTree()
		{
			inOrderPrint(root);
			printf("\n");
		}

		void inOrderPrint(Node* p)
		{
			if(p==NULL)
				return;
			else
			{
				inOrderPrint(p->left);
				cout<<p->val<<" ";
				inOrderPrint(p->right);
			}
		}

		//保证e在查找树中
		void deleteKey(int e)
		{
			Node* p=root;
			Node* parent=NULL;
			while(p!=NULL)
			{

				if(e==p->val)
					break;
				if(e>p->val)
				{
					parent=p;
					p=p->right;
				}
				else
				{
					parent=p;
					p=p->left;
				}
			}
			if(p!=root)//如果要删除的是根结点，要特殊处理
			{

				if(p->left==NULL&&p->right==NULL)//如果p是叶节点，可以直接删掉
				{
					if(parent->left==p)
						parent->left=NULL;
					else
						parent->right=NULL;
					delete p;
					return;
				}
				if((p->left==NULL&&p->right!=NULL)||(p->left!=NULL&&p->right==NULL))
				//p只有右子树或者左子树，把子树直接挂到p的父结点上去 
				{
					Node* child;
					if(p->left!=NULL)
						child=p->left;
					else
						child=p->right;
					if(parent->left==p)
					{
						parent->left=child;
					}
					else
						parent->right=child;
					delete p;
					return;
				}
				if(p->left!=NULL&&p->right!=NULL)//如果左右子树都有
					//采取的措施是把p的左子树接到父结点的左子树上，然后把p的右子树作为p中序遍历直接前驱的右子树
					// p中序遍历直接前驱的右子树必为空，p中序遍历直接前驱就是p左子树的最右结点
				{
					Node* inOrderPre=p->left;// inOrderPre就是p中序遍历直接前驱
					Node* tmp=p->left;
					while(tmp!=NULL)
					{
						inOrderPre=tmp;
						tmp=tmp->right;
					}
					parent->left=p->left;
					inOrderPre->right=p->right;
					delete p;
					return;

				}
			}
			else//如果删除的是根结点
			{
				if(p->left==NULL&&p->right==NULL)//如果只有一个根结点
				{
					delete p;
					root=NULL;//需要手动把指针变成空指针
					return;
				}
				if((p->left==NULL&&p->right!=NULL)||(p->left!=NULL&&p->right==NULL))//如果根结点只有左子树或者右子树
				{
					Node* child;
					if(p->left!=NULL)
						child=p->left;
					else
						child=p->right;
					root=child;
					delete p;
					return;
				}
				if(p->left!=NULL&&p->right!=NULL)//如果左右子树都有
					//采取的措施是把p的左子树的根当做根结点，然后把p的右子树作为p中序遍历直接前驱的右子树
					// p中序遍历直接前驱的右子树必为空，p中序遍历直接前驱就是p左子树的最右结点
				{
					Node* inOrderPre=p->left;// inOrderPre就是p中序遍历直接前驱
					Node* tmp=p->left;
					while(tmp!=NULL)
					{
						inOrderPre=tmp;
						tmp=tmp->right;
					}
					root=p->left;
					inOrderPre->right=p->right; 
					delete p;
					return;
				}

			}
		}

		~BinarySearchTree()
		{
			deleteTree(root);
			cout<<"二叉查找树已经被析构!"<<endl;
		}

		void deleteTree(Node* p)
		{
			if(p==NULL)
				return;
			if(p->left==NULL&&p->right==NULL)
			{
				delete p;
				return;
			}
			deleteTree(p->left);
			deleteTree(p->right);
		}
};

int main()
{
	int A[7]= {27,51,19,3,48,12,32};
	BinarySearchTree bst=BinarySearchTree(A,7);
	bst.printTree();
//	bst.insert(49);
	bst.printTree();
	bst.searchTree(19);
	bst.searchTree(7);
	//以下是删除叶节点
//	bst.deleteKey(49);
//	bst.deleteKey(12);
	//以下是删除只有左子树或右子树的结点
//    bst.deleteKey(48);
//    bst.deleteKey(3);
    //删除左右子树都有的结点 
	bst.insert(25);
	bst.insert(23);
//	bst.deleteKey(19);
	//删除根结点
	bst.deleteKey(27);
	bst.printTree();
}
