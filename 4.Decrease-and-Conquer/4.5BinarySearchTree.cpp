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
			Node* tmp=new Node(); //���������µĿռ䣬����Ⱥ���һ�������´����Ľ��ͻᱻ�ͷţ�root�ͻ��ΪҰָ�� 
			tmp->val=array[0];
			root=tmp;
			for(int i=1; i<n; i++)
				insert(array[i]);
		}

		void insert(int e)
		{
			Node* p=root;
			Node* parent=NULL;//parent����Ҫ������ĸ����
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
				cout<<"�ҵ���"<<p->val<<"\n";
				return true;
			}
			else
			{
				cout<<"û�ҵ�"<<e<<"\n";
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
					return search(e,p->right); //���ҲҪ��return �׸���һ�� 
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

		//��֤e�ڲ�������
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
			if(p!=root)//���Ҫɾ�����Ǹ���㣬Ҫ���⴦��
			{

				if(p->left==NULL&&p->right==NULL)//���p��Ҷ�ڵ㣬����ֱ��ɾ��
				{
					if(parent->left==p)
						parent->left=NULL;
					else
						parent->right=NULL;
					delete p;
					return;
				}
				if((p->left==NULL&&p->right!=NULL)||(p->left!=NULL&&p->right==NULL))
				//pֻ��������������������������ֱ�ӹҵ�p�ĸ������ȥ 
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
				if(p->left!=NULL&&p->right!=NULL)//���������������
					//��ȡ�Ĵ�ʩ�ǰ�p���������ӵ��������������ϣ�Ȼ���p����������Ϊp�������ֱ��ǰ����������
					// p�������ֱ��ǰ������������Ϊ�գ�p�������ֱ��ǰ������p�����������ҽ��
				{
					Node* inOrderPre=p->left;// inOrderPre����p�������ֱ��ǰ��
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
			else//���ɾ�����Ǹ����
			{
				if(p->left==NULL&&p->right==NULL)//���ֻ��һ�������
				{
					delete p;
					root=NULL;//��Ҫ�ֶ���ָ���ɿ�ָ��
					return;
				}
				if((p->left==NULL&&p->right!=NULL)||(p->left!=NULL&&p->right==NULL))//��������ֻ������������������
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
				if(p->left!=NULL&&p->right!=NULL)//���������������
					//��ȡ�Ĵ�ʩ�ǰ�p���������ĸ���������㣬Ȼ���p����������Ϊp�������ֱ��ǰ����������
					// p�������ֱ��ǰ������������Ϊ�գ�p�������ֱ��ǰ������p�����������ҽ��
				{
					Node* inOrderPre=p->left;// inOrderPre����p�������ֱ��ǰ��
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
			cout<<"����������Ѿ�������!"<<endl;
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
	//������ɾ��Ҷ�ڵ�
//	bst.deleteKey(49);
//	bst.deleteKey(12);
	//������ɾ��ֻ�����������������Ľ��
//    bst.deleteKey(48);
//    bst.deleteKey(3);
    //ɾ�������������еĽ�� 
	bst.insert(25);
	bst.insert(23);
//	bst.deleteKey(19);
	//ɾ�������
	bst.deleteKey(27);
	bst.printTree();
}
