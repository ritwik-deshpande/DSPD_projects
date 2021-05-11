#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct member_node_tag
{	
	char fname[20];
	char sname[20];
	char gender;
	float TEarns;
	int eduQ;
	int MS;
	int age;
	int isAlive;
}MNode;

typedef struct family_tree_node_tag
{
	int countchild;
	MNode member;
	MNode partner;
	float totalIncome;
	float SRec;
	float SCap;
	struct family_tree_node_tag* nextSib;
	struct family_tree_node_tag* s;
	struct family_tree_node_tag* d;
		
}FTNode;

typedef struct forest_list_node_tag
{
	FTNode* clan;
	struct forest_list_node_tag	*next;	
}ForNode;

FTNode* makeTreeNode(char* fname,char* sname,char gender,int TEarns,int age,int eduQ,int MS,int isAlive)
{
	FTNode* ptr;
	ptr=(FTNode*)malloc(sizeof(FTNode));
	ptr->countchild=0;
	strcpy(ptr->member.fname,fname);
	strcpy(ptr->member.sname,sname);
	strcpy(ptr->partner.fname,"NOT MARRIED");
	ptr->partner.isAlive=0;
	ptr->member.gender=gender;
	ptr->member.age=age;
	ptr->member.TEarns=TEarns;
	ptr->member.eduQ=eduQ;
	ptr->member.MS=MS;
	ptr->member.isAlive=isAlive;
	ptr->nextSib=NULL;
	ptr->totalIncome=TEarns;
	ptr->s=NULL;
	ptr->d=NULL;
	ptr->SRec=0;
	ptr->SCap=0;
	return ptr;
}

void mergeTreeNode(FTNode* ptr,FTNode* pptr)
{
	printf("Entered merge function\n");
	strcpy(ptr->partner.fname,pptr->member.fname);
	strcpy(ptr->partner.sname,pptr->member.sname);
	ptr->partner.gender=pptr->member.gender;
	ptr->partner.TEarns=pptr->member.TEarns;
	ptr->partner.eduQ=pptr->member.eduQ;
	ptr->partner.MS=pptr->member.MS;
	ptr->partner.age=pptr->member.age;
	ptr->partner.isAlive=pptr->member.isAlive;
	ptr->totalIncome=ptr->totalIncome+ptr->partner.TEarns;
}

void calcCap(FTNode* root,FTNode* prev,int* sumcapacity,int* totaleduQ,int* countIsAlive,FTNode** head)
{
	if(root!=NULL)
	{
		while(root!=NULL)
		{
			calcCap(root->s,root,sumcapacity,totaleduQ,countIsAlive,head);
			
			printf("\n%s %d\n",root->member.fname,root->countchild);
			if(prev->member.isAlive==1 || prev->partner.isAlive==1)
				root->SRec=0.1*(prev->totalIncome);
			else
			{
				if(prev->countchild==0)
				{
					(*head)->SRec+=(prev->totalIncome);
				}
				else
				{
					printf("%d\n",(prev->countchild));
					root->SRec=0.1*(prev->totalIncome) + (prev->totalIncome)/(prev->countchild);
				}
				
				(prev->totalIncome)=0;
			}
			root->SCap=root->totalIncome + root->SRec-(root->totalIncome)*0.1*(root->countchild);
			printf("Hello\n");
			if(root->member.isAlive==1 || root->partner.isAlive==1)
			{
				*sumcapacity+=root->SCap;
				*totaleduQ+=root->member.eduQ;
				(*countIsAlive)++;
			}
			
			calcCap(root->d,root,sumcapacity,totaleduQ,countIsAlive,head);
			root=root->nextSib;
		}
	}
}

void countChild(FTNode* root,FTNode* prev)
{
	if(root!=NULL)
	{
		while(root!=NULL)
		{
			countChild(root->s,root);
			countChild(root->d,root);
			if(root!=prev)
				(prev->countchild)++;
			root=root->nextSib;
		}
	}
}

FTNode* SearchName(FTNode* root,char* name,int found)
{
	FTNode* retval=NULL;
	if((root!=NULL)&&(!found))
	{
		if((strcmp(root->member.fname,name)!=0 && strcmp(root->partner.fname,name)!=0)&&(!found))
		{
			while((root!=NULL)&&(!found))
			{
				if((strcmp(root->member.fname,name)==0 || strcmp(root->partner.fname,name)==0)&&(!found))
				{
					retval=root;
					found=1;
				}
				else
				{
				retval=SearchName(root->s,name,found);
				if(retval==NULL)
				retval=SearchName(root->d,name,found);
				root=root->nextSib;
				}
				
			}
		}
		else
		{
			printf("Found match\n");
			retval=root;
			found=1;
		}
	}
	return retval;
}

FTNode* SearchDeath(FTNode* root,FTNode* prev,char* name,int found)
{
	FTNode* retval=NULL;
	if((root!=NULL)&&(!found))
	{
		if((strcmp(root->member.fname,name)!=0 && strcmp(root->partner.fname,name)!=0)&&(!found))
		{
			while((root!=NULL)&&(!found))
			{
				retval=SearchDeath(root->s,root,name,found);
				if(retval==NULL)
					retval=SearchDeath(root->d,root,name,found);
				root=root->nextSib;
			}
		}
		else
		{
			printf("Found match\n");
			retval=root;
			if(strcmp(root->member.fname,name)==0)
				root->member.isAlive=0;
			else
				root->partner.isAlive=0;
			
			if(root->member.isAlive==0 && root->partner.isAlive==0)
			{
				if(prev!=root)
				{
					printf("%s\n",prev->member.fname);
					printf("%s\n",root->member.fname);
					(prev->countchild)--;
				}
			}
			found=1;
		}
	}
	return retval;
}


void insertFTNode(ForNode **Forest)
{
	ForNode *fortemp,*fortemp1;
	int flag=0;
	FILE *fp;
	int len=1,a;
	FTNode* ptr;
	char str[50];
	char gender;
	char spouse[20];
	char fthname[20];
	char sname[20];
	char fname[20];
	int age;
	float income;
	int eduQ;
	int MS;
	int isAlive;
	fp=fopen("Family1.txt","r");
	printf("Entered Function\n");
	if(fp==NULL)
	{
		puts("Cannot Open File");
	}
	else
	{
		printf("-----------------------------------------------------------------------------------\n");
		while(fgets(str,50,fp)!=NULL)
		{
			int k=1;
			while(k<=10)
			{
				if(k>1)
					fgets(str,50,fp);
				a=strlen(str);
				str[a-1]='\0';//Done because it takes new line
				switch(k%10)
				{
					case 1:
					{
						int i=0;
						while(str[i]!=':')
							i++;
						int j=0;
						i++;
						while(str[i]!='\0')
						{
							fname[j]=str[i];
							j++;	
							i++;
						}
						fname[j]='\0';
						printf("The firstname is:%s\n",fname);
					}
					break;
					case 2:
					{
						int i=0;
						while(str[i]!=':')
							i++;
						i++;
						int j=0;
						while(str[i]!='\0')
						{
							fthname[j]=str[i];
							j++;	
							i++;
						}
						fthname[j]='\0';
						printf("The fathersname is:%s\n",fthname);
					}
					break;
					case 3:
					{
						int i=0;
						while(str[i]!=':')
							i++;
						int j=0;
						i++;
						while(str[i]!='\0')
						{
							spouse[j]=str[i];
							j++;	
							i++;
						}
						spouse[j]='\0';
						printf("The spousename is:%s\n",spouse);
					}
					break;
					case 4:
					{
						int i=0;
						while(str[i]!=':')
							i++;
						i++;
						gender=str[i];
						printf("The gender %c\n",gender);
					}
					break;
					case 5:
					{
						int i=0;
						char str1[10];
						while(str[i]!=':')
							i++;
						i++;
						int j=0;
						while(str[i]!='\0')
						{
							str1[j]=str[i];
							j++;	
							i++;
						}
						str1[j]='\0';
						age=atoi(str1);
						printf("%d\n",age);
					}
					break;
					case 6:
					{
						int i=0;
						char str1[10];
						while(str[i]!=':')
							i++;
						i++;
						int j=0;
						while(str[i]!='\0')
						{
							str1[j]=str[i];
							j++;	
							i++;
						}
						str1[j]='\0';
						income=atoi(str1);
						printf("%f\n",income);
					}
					break;
					case 7:
					{
						int i=0;
						char str1[10];
						while(str[i]!=':')
							i++;
						int j=0;
						i++;
						while(str[i]!='\0')
						{
							str1[j]=str[i];
							j++;	
							i++;
						}
						str1[j]='\0';
						eduQ=atoi(str1);
						printf("%d\n",eduQ);
					}
					break;
					case 8:
					{
						char str1[10];
						int i=0;
						while(str[i]!=':')
							i++;
						int j=0;
						i++;
						while(str[i]!='\0')
						{
							str1[j]=str[i];
							j++;	
							i++;
						}
						str1[j]='\0';
						MS=atoi(str1);
						printf("%d\n",MS);
					}
					break;
						case 9:
					{
							int i=0;
						while(str[i]!=':')
							i++;
						int j=0;
						i++;
						while(str[i]!='\0')
						{
							sname[j]=str[i];
							j++;	
							i++;
						}
						sname[j]='\0';
						printf("The Surname is:%s\n",sname);
					}
					break;
					case 0:
					{
						char str1[10];
						int i=0;
						while(str[i]!=':')
							i++;
						i++;
						int j=0;
						while(str[i]!='\0')
						{
							str1[j]=str[i];
							j++;	
							i++;
						}
						str1[j]='\0';
						isAlive=atoi(str1);
						printf("%d\n",isAlive);
					}
					break;	
				}
				
				k++;
			}
			printf("\n\n");
			printf("-----------------------------------------------------------------------------------\n");
			fortemp1=*Forest;
			while(fortemp1!=NULL && flag==0)
			{
				if(strcmp(fortemp1->clan->member.sname,sname)==0)
					flag=1;
				fortemp=fortemp1;	
				fortemp1=fortemp1->next;	
			}
			
			if((fthname[0]=='\0')&&(gender=='M')&& flag==0)
			{
					ptr=makeTreeNode(fname,sname,gender,income,age,eduQ,MS,isAlive);
					ForNode *forptr;
					forptr=(ForNode*)malloc(sizeof(ForNode));
					forptr->clan=makeTreeNode(ptr->member.fname,ptr->member.sname,ptr->member.gender,
											ptr->member.TEarns,ptr->member.age,ptr->member.eduQ,
												ptr->member.MS,ptr->member.isAlive);
					forptr->next=*Forest;
					*Forest=forptr;	
					free(ptr);
			}
			else
			{
				FTNode* merge,*ptr1;
				merge=SearchName(fortemp->clan,spouse,0);
				if(merge==NULL)
				{
					FTNode* nptr=SearchName(fortemp->clan,fthname,0);
					if(nptr==NULL)
						printf("Invalid Entry doesn't belong to this family\n");
					else
					{
						ptr=makeTreeNode(fname,sname,gender,income,age,eduQ,MS,isAlive);
						if(gender=='F')
						{
							//Performing insert at start operation
							ptr->nextSib=nptr->d;
							nptr->d=ptr;
						}
						else
						{
							ptr->nextSib=nptr->s;
							nptr->s=ptr;
						}
					}
				}
				else
				{
					ptr1=makeTreeNode(fname,sname,gender,income,age,eduQ,MS,isAlive);
					mergeTreeNode(merge,ptr1);
					free(ptr1);
					printf("Deleted ptr1\n");
				}
			}
		}
	}
}

typedef struct Queuetag
{
	FTNode *front;
	FTNode *rear;
}Queue;

void Initialise(Queue *qptr)
{
	qptr->front=NULL;
	qptr->rear=NULL;
}

int isQueueEmpty(Queue *qptr)
{
	int retval=0;
	if((qptr->front==NULL)&&(qptr->rear==NULL))
	{
		retval=1;
	}
	return retval;
}

void Push(Queue *qptr,FTNode *nptr)
{
		if((qptr->front==NULL)&&(qptr->rear==NULL))
		{
			qptr->front=nptr;
			qptr->rear=nptr;
			nptr->nextSib=NULL;
		}
		else
		{
			(qptr->rear)->nextSib=nptr;
			nptr->nextSib=NULL;
			qptr->rear=nptr;
		}
}

FTNode* Pop(Queue *qptr)
{
	FTNode *ptr;
		if(isQueueEmpty(qptr)==0)
		{
			ptr=qptr->front;
			qptr->front=(qptr->front)->nextSib;
			if(qptr->front==NULL)
			{
				qptr->rear=NULL;
			}
		}
		else
		{
			ptr=NULL;
		}
	return ptr;
}



void returnLevelNodes(FTNode *root,int level,Queue* q)
{	
	FTNode* temp;
	if (root == NULL)
        return;
    if (level == 0)
    {
    	while(root!=NULL)
    	{
    		temp=makeTreeNode(root->member.fname,root->member.sname,root->member.gender,
			root->member.TEarns,root->member.age,root->member.eduQ,
			root->member.MS,root->member.isAlive);
			temp->SRec=root->SRec;
			temp->SCap=root->SCap;
			temp->countchild=root->countchild;
			Push(q,temp);
	        root=root->nextSib;
    	}		
	}
    else if (level > 0)
    {
    	while(root!=NULL)
    	{
        returnLevelNodes(root->s, level-1,q);
        returnLevelNodes(root->d, level-1,q);
        root=root->nextSib;
    	}
    }		
}

void printHilow(FTNode* root,int level)
{
	Queue q1,q2;
	Initialise(&q1);
	Initialise(&q2);
	returnLevelNodes(root,level,&q1);
	FTNode *temp;
	float hiScap,loScap;
	int hieduQ,loeduQ;
	
		temp=Pop(&q1);
		hiScap=temp->SCap;
		loScap=temp->SCap;
		hieduQ=temp->member.eduQ;
		loeduQ=temp->member.eduQ;
		Push(&q2,temp);
	
	while(!isQueueEmpty(&q1))
	{
		temp=Pop(&q1);
		
		if(hiScap<temp->SCap)
		hiScap=temp->SCap;
		if(loScap>temp->SCap)
		loScap=temp->SCap;
		if(hieduQ<temp->member.eduQ)
		hieduQ=temp->member.eduQ;
		if(loeduQ>temp->member.eduQ)
		loeduQ=temp->member.eduQ;
		
		Push(&q2,temp);
	}
	
	printf("\nHighest Saving Capacity :");
	while(!isQueueEmpty(&q2))
	{
		temp=Pop(&q2);
		if(temp->SCap==hiScap)
		printf("\n%s---->%f",temp->member.fname,temp->SCap);
		Push(&q1,temp);
	}
	
		printf("\nLowest Saving Capacity :");
	while(!isQueueEmpty(&q1))
	{
		temp=Pop(&q1);
		if(temp->SCap==loScap)
		printf("\n%s---->%f",temp->member.fname,temp->SCap);
		Push(&q2,temp);
	}
	
			printf("\nHighest Educational Qualification :");
	while(!isQueueEmpty(&q2))
	{
		temp=Pop(&q2);
		if(temp->member.eduQ==hieduQ)
		printf("\n%s---->%d",temp->member.fname,temp->member.eduQ);
		Push(&q1,temp);
	}
	
				printf("\nLowest Educational Qualification :");
	while(!isQueueEmpty(&q1))
	{
		temp=Pop(&q1);
		if(temp->member.eduQ==loeduQ)
		printf("\n%s---->%d",temp->member.fname,temp->member.eduQ);
		free(temp);
	}
}

int Height(FTNode* root)
{
	int retval,lht,rht,temp;
	static int max=-1;
	if(root==NULL)
		retval=-1;
	else if(root->s==NULL && root->d==NULL)
		retval=0;
	else
	{
		while(root!=NULL)
		{
			lht=Height(root->s);
			rht=Height(root->d);
			
			if(lht>rht)
			{
				retval=1+lht;
			}
			else
				retval=1+rht;
			if(max<retval)
				max=retval;
			root=root->nextSib;
		}
	}
	
	return retval;			
}

void printAliveNodes(FTNode* root)
{
	Queue q;
	Initialise(&q);
	int height=Height(root);
	int found=0,i=0;
	FTNode* temp;
	
	printf("\nAlive members are ");
	while(!found && i<=height)
	{
		returnLevelNodes(root,i,&q);
		while(!isQueueEmpty(&q))
		{
			temp=Pop(&q);
			if(temp->member.isAlive==1 || temp->partner.isAlive==1)
			{
				found=1;
				if(temp->member.isAlive==1 && temp->partner.isAlive==1)
				printf("\n%s   %s",temp->member.fname,temp->partner.fname);
				else if(temp->member.isAlive==1)
				printf("\n%s",temp->member.fname);
				else
				printf("\n%s",temp->partner.fname);
			}
			free(temp);
		}
		if(found==1)
		printf("\nHighest Level no. %d",i);
		i++;
	}
	
	found=0;
	i=Height(root);
		printf("\nAlive members are ");
	while(!found && i>=0)
	{
		returnLevelNodes(root,i,&q);
		while(!isQueueEmpty(&q))
		{
			temp=Pop(&q);
			if(temp->member.isAlive==1 || temp->partner.isAlive==1)
			{
				found=1;
				if(temp->member.isAlive==1)
				printf("\n%s",temp->member.fname);
				else
				printf("\n%s",temp->partner.fname);
			}
			free(temp);
		}
		if(found==1)
		printf("\nLowest Level no. %d",i);
		i--;
	}
}

void returnHead(FTNode *root,int level,FTNode** head,int maxage)
{	
	FTNode* temp;
	if (root == NULL)
        	return;
	    if(level == 0)
	    {
	    	while(root!=NULL)
	    	{
	    		if(maxage<root->member.age && (root->member.isAlive==1 || root->partner.isAlive==1))
	    		{
	    			maxage=root->member.age;
	    			*head=root;
				}
			root=root->nextSib;
	    	}		
	}
    else if (level > 0)
    {
    	while(root!=NULL)
    	{
        returnHead(root->s, level-1,head,maxage);
        returnHead(root->d, level-1,head,maxage);
        root=root->nextSib;
    	}
    }		
}

FTNode* findHead(FTNode* root)
{
	FTNode* head=NULL;
	int i=0;
	int h=Height(root);
	int found=0;
	while(i<h && !found)
	{
		returnHead(root,i,&head,0);
		i++;
		if(head!=NULL)
			found=1;
	}
	return head;
}

void spendingCapacity(FTNode* root1,FTNode* root2)
{
	int sumcapacity1=0, totaleduQ1=0, countIsAlive1=0;
	int sumcapacity2=0, totaleduQ2=0, countIsAlive2=0;
	FTNode* head1=findHead(root1);
	FTNode* head2=findHead(root2);
	calcCap(root1,root1,&sumcapacity1,&totaleduQ1,&countIsAlive1,&head1);
	calcCap(root2,root2,&sumcapacity2,&totaleduQ2,&countIsAlive2,&head2);
	int spendcap1,spendcap2,avgeduQ1,avgeduQ2;
	spendcap1=sumcapacity1/countIsAlive1;
	spendcap2=sumcapacity2/countIsAlive2;
	avgeduQ1=totaleduQ1/countIsAlive1;
	avgeduQ2=totaleduQ2/countIsAlive2;
	printf("\n Spending Capacity of %s clan is %d",root1->member.sname,spendcap1);
	printf("\n Spending Capacity of %s clan is %d",root2->member.sname,spendcap2);
	printf("\n Average Educational Qualification of %s clan is %d",root1->member.sname,avgeduQ1);
	printf("\n Average Educational Qualification of %s clan is %d",root2->member.sname,avgeduQ2);
}

void levelSpendingCapacity(FTNode* root,int level)
{
	Queue q;
	Initialise(&q);
	FTNode* temp;
	float sum=0;
	float aliveCount=0;
	
	returnLevelNodes(root,level,&q);
	while(!isQueueEmpty(&q))
	{
		temp=Pop(&q);
		if(temp->member.isAlive==1 || temp->partner.isAlive==1)
		{
			sum=sum + temp->SCap;
			aliveCount++;
		}
		free(temp);
	}
	float spendCapacity= sum/aliveCount;
	printf("\nSpending Capacity per Person for level no %d is---> %f",level,spendCapacity);
}

int checkFamily(FTNode* root,char *name1, char* name2,int found1,int found2,int match)
{
	if((root!=NULL)&&(!match))
	{
		if((found1==0)||(found2==0))
		{
			while((root!=NULL)&&(!match))
			{
				if((strcmp(root->member.fname,name1)==0 || strcmp(root->partner.fname,name1)==0)&&(!found1))
				{
					found1=1;
				}
				if((strcmp(root->member.fname,name2)==0 || strcmp(root->partner.fname,name2)==0)&&(!found2))
				{
					found2=1;
				}
				if((found1==1)&&(found2==1))
				{
					printf("Match found\n");
					match=1;
				}
				else
				{
					match=checkFamily(root->s,name1,name2,found1,found2,match);
					if(match==0)
						match=checkFamily(root->d,name1,name2,found1,found2,match);
					root=root->nextSib;
				}
			}
		}
		
	}
	return match;
}
int main()
{
	ForNode *Forest=NULL;
	FTNode* root=NULL, *retNode=NULL,*head=NULL;
	insertFTNode(&Forest);
	Queue q;
	Initialise(&q);
	
	returnLevelNodes(Forest->clan, 4, &q);
	while(!isQueueEmpty(&q))
	{
		retNode=Pop(&q);
		printf("\n%s-----------------------------------",retNode->member.fname);
		free(retNode);
	}
	
	countChild(Forest->clan, Forest->clan);
	SearchDeath(Forest->clan,Forest->clan, "Malti", 0);
	SearchDeath(Forest->clan,Forest->clan, "Shankar", 0);
	SearchDeath(Forest->clan,Forest->clan, "Shankar1", 0);
	SearchDeath(Forest->clan,Forest->clan, "Malti2", 0);
	
	
	int sumcapacity=0, countIsAlive=0, totaleduQ=0;
	head=findHead(Forest->clan);
	printf("%s",head->member.fname);
	calcCap(Forest->clan, Forest->clan, &sumcapacity, &totaleduQ, &countIsAlive,&head);
	calcCap(Forest->clan, Forest->clan, &sumcapacity, &totaleduQ, &countIsAlive,&head);
	printHilow(Forest->clan, 3);
	int height=Height(Forest->clan);
	printf("Height--->%d", height);
	printAliveNodes(Forest->clan);
	spendingCapacity(Forest->clan, Forest->clan);
	levelSpendingCapacity(Forest->clan,3);
	char name1[20],name2[20];
	printf("Enter the two names that we have to enter to check if they are from same family:\n");
	scanf("%s%s",name1,name2);
	ForNode* ptr=Forest;
	int match=0;
	while((ptr!=NULL)&&(!match))
	{
		match=checkFamily(ptr->clan,name1,name2,0,0,0);
		if(match)
			printf("They belong to the same family!");
		ptr=ptr->next;
		
	}
	if(!match)
		printf("They do not belong to the same family\n");
	return 0;
}


