#include<stdio.h>
#include<stdlib.h>
#define N 5
typedef struct nodeTag
{
	int data;
	struct nodeTag * next;
}node;

typedef struct queueTag
{
	node * front;
	node * rear;
}queue;

void insert(queue *aptr, int d)
{
	node *ptr;
	ptr=(node *)malloc(sizeof(node));
	ptr->data=d;
	ptr->next=NULL;
	if(aptr->front==NULL)
	{
		aptr->front=ptr;
		aptr->rear=ptr;
	}
	else
	{
		(aptr->rear)->next=ptr;
		aptr->rear=ptr;
	}
}

void delete(queue *aptr)
{	
	node *ptr;
	if(aptr->front==NULL)
	{
		printf("Queue is empty\n");
	}
	else
	{
		ptr=aptr->front;
		aptr->front=(aptr->front)->next;
		printf("Data deleted: %d",ptr->data);
		free(ptr);
	}
}	
		
void print(queue priArray[])
{
	int i;
	node *ptr;
	for(i=0;i<N;i++)
	{
		ptr=priArray[i].front;
		while(ptr!=NULL)
		{
			printf("%d\t",ptr->data);
			ptr=ptr->next;
		}
		printf("\n");
	}
}	
	
void main()
{
	queue priArray[N];
	int n,pri,d,i,flag=1;
	for(i=0;i<N;i++)
	{
		priArray[i].front=NULL;
		priArray[i].rear=NULL;
	}
	do
	{
		printf("\n1.Insert\n2.Delete\n3.Print\n4.Exit\n");
		scanf("%d",&n);		
		switch(n)
		{
			case 1:
			printf("Priority(0-4): ");
			scanf("%d",&pri);
			if(pri>=0&&pri<=4)
			{
				printf("Data: ");
				scanf("%d",&d);
				insert(&priArray[pri],d);
			}
			else
			{
				printf("Enter valid priority number\n");
			}
			break;
		
			case 2:
			printf("Priority(0-4): ");
			scanf("%d",&pri);
			if(pri>=0&&pri<=4)
			{
				delete(&priArray[pri]);
			}
			else
			{
				printf("Enter valid priority number\n");
			}
			break;
		
			case 3:
			print(priArray);
			break;
			
			case 4:
			flag=0;
			break;
		}
	}
	while(flag==1);
}
		
		
		
