#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct nodeTag
{
	char data[10];
	int strln;
	struct nodeTag *next;
}node;

typedef struct pointerTag
{
	node * front;
	node * rear;
}pointer;

void main()
{
	int i,n,max=0,j,k,len,flag;
	pointer A[27];
	char temp[10];
	for(i=0;i<27;i++)
	{
		A[i].front=NULL;
		A[i].rear=NULL;
	}
	node *ptr,*head,*ahead;
	head=NULL;
	printf("Enter number of elements");
	scanf("%d",&n);
	printf("Enter elements:\n");
	for(i=0;i<n;i++)
	{
		ptr=(node*)malloc(sizeof(node));
		scanf("%s",temp);
		len=strlen(temp);
		ptr->strln=len;
		if(max<len)
		{
			max=len;
		}
		strcpy(ptr->data,temp);
		ptr->next=head;
		head=ptr;
	
	}
	for(i=0;i<max;i++)
	{
		ptr=head;
		while(ptr!=NULL)
		{
			len=ptr->strln;			
			if(len<(max-i))
			{
				j=0;
			}
			else
				j=ptr->data[max-1-i]-'a'+1;
			if(A[j].front==NULL)
			{
				A[j].front=ptr;
				A[j].rear=ptr;
				ptr=ptr->next;
				A[j].rear->next=NULL;
			}
			else
			{
				(A[j].rear)->next=ptr;
				A[j].rear=ptr;
				ptr=ptr->next;
				A[j].rear->next=NULL;
			}
			
		}
		j=0;
		while((j<27)&&(A[j].front==NULL))
		{
			j++;
		}
		head=A[j].front;
		for(k=j+1;k<26;k++)
		{
			while((k<27)&&(A[k].front==NULL))
			{
				k++;
				flag=0;
			}
			if(k<27)
			{			
				A[j].rear->next=A[k].front;
			}
			j=k;
		}
		for(k=0;k<27;k++)
		{
			A[k].front=NULL;
			A[k].rear=NULL;
		}
	}
	printf("\n\n");
	while(head!=NULL)
	{
		printf("%s\n",head->data);
		head=head->next;
	}
}
		
			
		
	
		


