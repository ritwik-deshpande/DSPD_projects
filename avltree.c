#include<stdio.h>
#include<stdlib.h>

typedef struct tree_node_tag
{
	int data;
	struct tree_node_tag* left;
 	struct tree_node_tag* right;
}TreeNode;
typedef struct List_Node_Tag
{
    TreeNode** data;
    struct List_Node_Tag *next;
}List_Node;

TreeNode* insertTree(TreeNode* node,TreeNode* root)
{
	TreeNode* p=root;
	int done=0;
	if(root==NULL)
		root=node;
	else
	{
		while(!done)
		{
			if((p->data)>(node->data))
			{
				if(p->left==NULL)
				{
					done=1;
					p->left=node;
				}
				else
					p=p->left;
			}
			else if((p->data)<(node->data))
			{
				if(p->right==NULL)
				{
					done=1;
					p->right=node;
				}
				else
					p=p->right;
			}
			else
			{
				printf("Data entry already present\n");
				done=1;
			}
		}
	}
	return root;
}
int height(TreeNode* root)
{
	int h1,h2,retval;
	if(root==NULL)
		retval=-1;
	else if((root->left==NULL)&&(root->right==NULL))
		retval=0;
	else
	{
		h1=height(root->left);
		h2=height(root->right);
		if(h1>h2)
			retval=1+h1;
		else if(h1<h2)
			retval=1+h2;
	}
	return retval;
}

void Inorder(TreeNode* root)
{
		if(root!=NULL)
		{
			
			Inorder(root->left);
			printf("%d\t",root->data);
			Inorder(root->right);
		}
}


int main()
{
	int i=0,n,num;
	TreeNode* root=NULL;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&num);
		TreeNode* p;
		p=makenode(p,num);
		root=insertTree(p,root);
	}
	
	return 0;
}
