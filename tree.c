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
typedef struct Queue_Tag
{
    List_Node *front;
    List_Node *rear;
}Queue_type;

void Initialise (Queue_type *qptr)
{
    printf("Eneterd initialize function\n");
    qptr->front=NULL;
    qptr->rear=NULL;
}

List_Node *Make_Node(TreeNode** data)
{
    List_Node *ptr;
    ptr=(List_Node *)malloc(sizeof(List_Node));
    if(ptr!=NULL)
    {
        ptr->data=data;
        ptr->next=NULL;
    }
    return ptr;
}

int isQueueEmpty(Queue_type *qptr)
{
    int res=0;
    if(qptr->front==NULL && qptr->rear==NULL)
    {
        res=1;
    }
    return res;
}

void Insert_Queue(Queue_type *qptr,TreeNode** d)
{
    List_Node *ptr=Make_Node(d);
    if(ptr!=NULL)
    {
        if(isQueueEmpty(qptr))
        {
            qptr->front=ptr;
            qptr->rear=ptr;
            ptr->next=NULL;
        }
        else
        {
            (qptr->rear)->next=ptr;
            ptr->next=NULL;
            qptr->rear=ptr;
        }
    }
}

TreeNode** Delete_Queue(Queue_type *qptr,TreeNode** dptr)
{
    List_Node *ptr;
    if(!isQueueEmpty(qptr))
    {
        ptr=qptr->front;
        qptr->front=(qptr->front)->next;
        dptr=ptr->data;
        free(ptr);
        if (qptr->front ==NULL)
        {
            qptr->rear=NULL;
        }
    }
	return dptr;
}
TreeNode* makenode(TreeNode* root,int data)
{
	TreeNode* p;
	p=(TreeNode*)malloc(sizeof(TreeNode));
	p->data=data;
	root=p;
	return root;
}

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
TreeNode* rotateLeft(TreeNode* p)
{
	TreeNode* q;
	printf("Entered functiopn\n");
	if(p==NULL)
	{
		printf("Not possible!!\n");
		q=p;
	}
	else if(p->right==NULL)
	{
		printf("Not possible!!\n");
		q=p;
	}
	else
	{
		q=p->right;
		p->right=q->left;
		q->left=p;
	}
	return q;
}

TreeNode* rotateRight(TreeNode* p)
{
	TreeNode* q;
	printf("NEtered function\n");
	if(p==NULL)
	{
		printf("Not possible!!\n");
		q=p;
	}
	else if(p->left==NULL)
	{
		printf("Not possible!!\n");
		q=p;
	}
	else
	{
		q=p->left;
		p->left=q->right;
		q->right=p;
	}
	return q;
}
TreeNode* insertavl(TreeNode* node,TreeNode* root)
{
	printf("Eneterd insert function\n");
	if(root==NULL)
		root=node;
	else
	{
		if(root->data<node->data)
		{
			if(root->right==NULL)
				root->right=node;
			else
				insertavl(node,root->right);
		}
		else
		{
			if(root->left==NULL)
				root->left=node;
			else
				insertavl(node,root->left);
		}
	}
	int h=height(root->left)-height(root->right);
	printf("%d\n",h);
	TreeNode* ptr1=root->left;
	TreeNode* ptr2=root->right;
	if(h>1)
	{
		if(ptr1!=NULL && ptr2!=NULL)
		{
			int h1=height(ptr1->right)-height(ptr1->left);
			if(h1<-1)
			{
				rotateLeft(ptr1);
				rotateRight(root);
			}
			else
				rotateRight(root);
		
		}
	}
	else if(h<-1)
	{
		int h1=height(ptr2->right)-height(ptr2->left);
			if(h1<-1)
			{
				rotateRight(ptr2);
				rotateLeft(root);
			}
			else
				rotateLeft(root);
		
	}
	return root;
}
void Preorder(TreeNode* root)
{
	if(root!=NULL)
	{
		printf("%d\t",root->data);
		Preorder(root->left);
		Preorder(root->right);
	}
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

void Postorder(TreeNode* root)
{
	if(root!=NULL)
	{
		Preorder(root->left);
		Preorder(root->right);
		printf("%d\t",root->data);
	}
}

void DeleteNode(TreeNode* ptr,TreeNode* prev)
{
	TreeNode* tail=ptr,*tail2,*temp,*tail1;
	if(ptr!=NULL)
	{	printf("ugegfoewigf");
		if(prev->right==ptr)
		{
			if((ptr->right==NULL)||(ptr->left==NULL))
			{
				if(ptr->right==NULL)
				{
					prev->right=ptr->left;
					free(ptr);
				}
				else if(ptr->left==NULL)
				{
					prev->right=ptr->right;
					free(ptr);
				}
			}
			else
			{
				tail2=ptr->right;
				tail=ptr->left;
				tail1=ptr->left;
				if(tail->left!=NULL)
				{
					while(tail->right!=NULL)
					{
						temp=tail;
						tail=tail->right;
					}
					temp->right=tail->left;
					tail->right=tail2;
					tail->left=tail1;
					prev->right=tail;
					free(ptr);
				}
				else
				{
					prev->right=tail;
					free(ptr);					
				}
			}
		}
		else if(prev->left==ptr)
		{
			if((ptr->right==NULL)||(ptr->left==NULL))
			{
				if(ptr->right==NULL)
				{
					prev->left=ptr->left;
					free(ptr);
				}
				else if(ptr->left==NULL)
				{
					prev->left=ptr->right;
					free(ptr);
				}
			}
			else
			{
				tail2=ptr->right;
				tail=ptr->left;
				tail1=ptr->left;
				if(tail->left!=NULL)
				{
					while(tail->right!=NULL)
					{
						temp=tail;
						tail=tail->right;
					}
					temp->right=tail->left;
					tail->right=tail2;
					tail->left=tail1;
					prev->left=tail;
					free(ptr);
				}
				else
				{
					prev->left=tail;
					free(ptr);					
				}
			}
		}
	}
		
}
TreeNode* Delete(TreeNode* root,int key)
{
	//Find *match
	TreeNode* p=root,*prev=NULL;
	while((p!=NULL)&&(p->data!=key))
	{
		if(p->data>key)
		{	
			prev=p;
			p=p->left;
		}
		else
		{
			prev=p;
			p=p->right;
		}
	}
	if(p!=NULL)
	{
		if(p==root)
			DeleteNode(p,prev);
		else
			DeleteNode(p,prev);
	}
	return root;
}

int cnl(TreeNode* root)
{
	static int count=1,retval;
	if(root==NULL)
		count=0;
	else
	{
		
		if((root->left!=NULL)||(root->right!=NULL))
		{
			count++;
			if(root->left!=NULL)
				cnl(root->left);
			if(root->right!=NULL)
				cnl(root->right);
		}
		else
			count--;
	}
	return count;
}
void insertheap(int a[],int l,int h,int key)
{
	printf("Eneterd heap\n");
	int large=2*l+1;
	int flag=0;
	while((large<=h)&&(flag==0))
	{
		if((large<h)&&(a[large]<a[large+1]))
			large++;
		if(a[large]<key)
			flag=1;
		else
		{
			printf("Swapped %d and %d\n",a[l],a[large]);
			a[l]=a[large];
			l=large;
			large=2*l+1;
		}
	}
	a[l]=key;
}
void levelorder(TreeNode* root,Queue_type* qptr)
{
	Initialise(qptr);
	Insert_Queue(qptr,&(root));
	do
	{
		TreeNode** t;
		t=Delete_Queue(qptr,t);
		root=*t;
		printf("%d\t",(root->data));
		if(root!=NULL)
		{	
			if(root->left!=NULL)
				Insert_Queue(qptr,&(root->left));
			if(root->right!=NULL)
				Insert_Queue(qptr,&(root->right));
		}
		
	}while(!isQueueEmpty(qptr));
}
void BuildMax(int a[],int n)
{
	int i;
	printf("Eneterd buildmax function\n");
	for(i=n/2-1;i>=0;i--)
	{
		insertheap(a,i,n-1,a[i]);
	}
}
void checkComplete(TreeNode* root,int* a,int i)//Also form a complelte binaryy tree
{
	if(root!=NULL)
	{
		printf("%d\n",(root->data));
		if(root->left!=NULL)
		{
			a[2*i+1]=(root->left)->data;
			printf("%d is leftchild of %d  inserted aat %d \n",a[2*i+1],(root->data),(2*i+1));
		}
		if(root->left==NULL)
		{
			if(a[2*i+1]==0)
				a[2*i+1]=-1;
		}
		if(root->right!=NULL)
		{
			a[2*i+2]=(root->right)->data;
			printf("%d is right child of %d inserted at %d \n",a[2*i+2],(root->data),(2*i+2));
		}
		if(root->right==NULL)
		{
			if(a[2*i+2]==0)
				a[2*i+2]=-1;
		}
		checkComplete(root->left,a,i+1);
		checkComplete(root->right,a,i+1);
	}
}


TreeNode* AVL(TreeNode* ptr)
{
	TreeNode* root=ptr;
	int dif,dif2;
	if((root!=NULL)&&((root->left!=NULL)||(root->right!=NULL)))
	{
		dif=(height(root->left)-height(root->right));
		if(abs(dif)>1)
		{
			if(dif<0)
			{
				/*dif2=height((root->right)->right)-height((root->right)->left);
				if(dif2<0)
				{
					printf("ewukw\n");
					root->right=rotateRight(root->right);
					root=rotateLeft(root);
				}*/
				//else
					root=rotateLeft(root);
			}
			else
			{
				/*dif2=height((root->left)->right)-height((root->left)->left);
				if(dif2>0)
				{
					root->left=rotateLeft(root->left);
					root=rotateRight(root);
				}
				else*/
					root=rotateRight(root);
			}
		}
		AVL(root->left);
		AVL(root->right);
	}
}
void Max3(TreeNode* root,int* max1,int* max2,int* max3)
{
	int temp;
	if(root!=NULL)
	{
		if(*max1<root->data)
		{
			if(*max1>*max2)
			{
				temp=*max2;
				*max2=*max1;
			}
			if(*max2>*max3)
				*max3=temp;
			*max1=root->data;
		}
		else if((*max2<root->data)&&(root->data!=*max1))
		{
			if(*max2>*max3)
				*max3=*max2;
			*max2=root->data;
		}
		else if((*max3<root->data)&&(root->data!=*max2))
		{
			*max3=root->data;
		}
		Max3(root->left,max1,max2,max3);
		Max3(root->right,max1,max2,max3);
	}
}
void heapSort(int a[],int n)
{
	int current,pos;
	for(pos=n-1;pos>=0;pos--)
	{
		current=a[pos];
		a[pos]=a[0];
		insertheap(a,0,pos-1,current);
	}
}
int main()
{
	TreeNode* root=NULL;
	int n,i,max1=0,max2=0,max3=0,h;
	scanf("%d",&n);
	int a[n],flag=0;
	int value[n];
	for(i=0;i<n;i++)
	{
		int num;
		printf("Enter values\n");
		scanf("%d",&num);
		value[i]=num;
		TreeNode* p;
		p=makenode(p,num);
		root=insertavl(p,root);
		a[i]=0;
	}
	//Preorder(root);
	//int count =cnl(root);
	//printf("No of non leaf node are:%d\n",count);
	//Max3(root,&max1,&max2,&max3);
	//printf("%d\t%d\t%d\t\n",max1,max2,max3);
	//h = height(root);
	//printf("%d\n",h);
	//Delete(root,n);
	//Inorder(root);
	Queue_type qptr;
	levelorder(root,&qptr);
	//heapSort(value,n);
	//root=AVL(root);
	/*BuildMax(value,n);
	for(i=0;i<n;i++)
	{
		printf("%d\t",value[i]);
	}
	heapSort(value,n);
	for(i=0;i<n;i++)
	{
		printf("%d\t",value[i]);
	}*/
	/*a[0]=root->data;
	checkComplete(root,a,0);
	for(i=0;i<n;i++)
	{
		printf("%d\n",a[i]);
		if(a[i]==-1)
		{
			printf("entered if\n");
			printf("%d\n",i);
			flag=1;
		}
	}
	if(flag==1)
		printf("Not a complete binary tree\n");*/
	return 0;
}
