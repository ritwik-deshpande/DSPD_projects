#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define TOTAL_OPERATIONS 10

int SIZE;

typedef enum{debit,credit,Abort,revert,failure}Sub_op; 
typedef struct transaction_tag
{	
	int tid;
	Sub_op operation;
	int sacc;
	int tacc;
	int amt;
	int pair1;
	int pair2;
	int inb;
	int incs;
	char *time;
	struct transaction_tag *next;

}Transaction;

typedef struct account_details
{
	int balance;
	int account_id;
	struct account_details *next;	
}Account;

char * getTime()
{
	time_t rawtime;
	char * timeinfo;
	rawtime=time(NULL);
	timeinfo=ctime(&rawtime);
	return timeinfo;
}

char * PrintOperation(Transaction *ptr)
{
	int s=ptr->operation;
	char* subop;
	subop=(char*)malloc(6*sizeof(char));
	switch(s)
	{
		case 0:strcpy(subop,"Debit");
			break;
		case 1:strcpy(subop,"Credit");
			break;
		case 2:strcpy(subop,"Abort");
			break;
		case 3:strcpy(subop,"Revert");
			break;			
	}
	return subop;
}

Account* inputAccountDetails(Account *a,int* c)
{
	FILE *fp;
	int len=1,i;
	Account *ptr;
	char str[50];
	fp=fopen("AccountDetails.txt","r");
	if(fp==NULL) {
		puts("Cannot Open File");
	}
	else
	{
		*c=0;
		while(fgets(str,50,fp)!=NULL)
		{
			i=strlen(str);
			str[i-1]='\0';
			switch (len%2)
			{
				case 1:
					ptr=(Account*)malloc(sizeof(Account));
      				   	ptr->account_id = atoi(str);//Converts String to integer.
					break;
				case 0:
					ptr->balance = atoi(str);
					break;
			}
			if(len%2==0)
			{
				*c=*c+1;
				 ptr->next=a;
				 a=ptr;
			}
			len++;
		}
	}
	fclose(fp);
	return a;
}



Transaction* Reverse(Transaction *lptr)
{
	Transaction *tail,*middle,*head,*rlptr;
	head=lptr;
	middle=NULL;
	
	while(head!=NULL)
	{
		tail=middle;
		middle=head;
		head=head->next;
		middle->next=tail;
	}
	
	rlptr=middle;
	return rlptr;
}

Account* ReverseA(Account *lptr)
{
	Account *tail,*middle,*head,*rlptr;
	head=lptr;
	middle=NULL;
	
	while(head!=NULL)
	{
		tail=middle;
		middle=head;
		head=head->next;
		middle->next=tail;
	}
	
	rlptr=middle;
	return rlptr;
}

int search(Transaction* lptr,int saccno,int taccno,Sub_op s,int amount,int* paired1,int* paired2)
{
	Transaction *ptr=lptr;
	int found=0;
	int retval=-1;
	
	if(s==credit)
	{
		
		while(ptr!=NULL && found==0)
		{
			if(ptr->sacc==saccno && ptr->tacc==taccno && ptr->amt==amount && ptr->pair1==0 && ptr->operation==debit && ptr->pair2==0 )
			{
				found=1;
				ptr->pair1=1;
				retval=ptr->tid;
				*paired1=1;
			}
			ptr=ptr->next;
		}

	}
	else if(s==Abort)
	{
		while(ptr!=NULL && found==0)
		{
			if(ptr->sacc==saccno && ptr->tacc==taccno && ptr->amt==amount && ptr->pair1==0 && ptr->operation==debit && ptr->pair2==0 )
			{
				found=1;
				ptr->pair2=1;
				retval=ptr->tid;
				*paired2=1;
			}
			ptr=ptr->next;
		}
	}
	else
	{
		int f=0;
		
		while(ptr!=NULL && found==0)
		{
			if(ptr->sacc==saccno && ptr->tacc==taccno && ptr->amt==amount)
			{
				if(ptr->operation==credit && ptr->pair1==1)
				{
					found=1;
					ptr->pair2=1;
					*paired2=1;
					*paired1=4;
					while(ptr!=NULL && f==0)
					{
					       if(ptr->sacc==saccno && ptr->tacc==taccno && ptr->amt==amount && ptr->pair1==1 && ptr->pair2==0)
					        {
							ptr->pair2=1;
							ptr->pair1=1;
							f=1;		
							retval=ptr->tid;
						}
						ptr=ptr->next;
					}
				}
				else if(ptr->operation==debit && ptr->pair1==0)
				{
					*paired1=3;
					*paired2=1;
					ptr->pair2=1;
					ptr->pair1=0;
					found=1;
					retval=ptr->tid;
				}
				else if(ptr->pair2==1)
				{
					found=1;
					retval=-1;
				}
			
			}
			if(ptr!=NULL)
				ptr=ptr->next;
		}

	}
	return retval;
}
void printlist(Transaction* lptr)
{
	Transaction *ptr=lptr;
	while(ptr!=NULL)
	{
		printf("Transaction Id:%d\nSource Account Number:%d\nTarget Account Number:%d\nAmount of Transaction:%d\nSub-operation:%s\nTime-Stamp:%s\n",(ptr->tid),(ptr->sacc),(ptr->tacc),(ptr->amt),PrintOperation(ptr),(ptr->time));
		
		ptr=ptr->next;
	}
}	

void printmessage(Transaction* lptr,Account *a)
{
	Transaction* ptr=lptr,*ptr2;
	Account *temp=a;
	Sub_op s=ptr->operation;
	switch(s)
	{
		case 0:
		{
			while(temp->account_id != ptr->sacc)
			temp=temp->next;
			
			int balance=temp->balance - ptr->amt;
			if(balance>=0)
			{
			printf("\nDebited Succesfully.\nThe amount debited in account %d is %d\nThe remaining balance is %d\n\n",(ptr->sacc),(ptr->amt),balance);	
			temp->balance -= ptr->amt;		
			}
			else
			{
				printf("Unsuccessful Debit due to insufficient balance\n");
				ptr->inb=1;
				ptr2=ptr;
				while(ptr2!=NULL)
				{
					if(ptr2->tid==ptr->tid)
					{
						ptr2->inb=1;
					}
					ptr2=ptr2->next;
				}	
			}
			
		}
		break;

		case 1:
		if(ptr->inb!=1)
		{
				temp=a;
			while(temp->account_id != ptr->tacc)
			temp=temp->next;
			
			temp->balance=temp->balance + ptr->amt;
			printf("\nCredited Succesfully.\nThe amount credited in account %d is %d\nThe remaining balance is %d\n\n",(ptr->tacc),(ptr->amt),temp->balance);
		}
		break;

		case 2:
		if(ptr->inb!=1)
		{
				temp=a;
			while(temp->account_id != ptr->sacc)
			temp=temp->next;
			
			temp->balance=temp->balance + ptr->amt;
			printf("\nAborted Succesfully.\nThe remaining balance in account %d is %d\n\n",(ptr->sacc),temp->balance);
			
		}
		break;
		
		case 3:
		if(ptr->inb!=1)
		{
			if(ptr->pair1==3)
			{
					temp=a;
			while(temp->account_id != ptr->sacc)
			temp=temp->next;
			
			temp->balance=temp->balance + ptr->amt;
				
				printf("\nReverted Succesfully.\nThe remaining balance in account %d is %d\n\n",(ptr->sacc),temp->balance);
			}
			if(ptr->pair1==4)
			{
					temp=a;
			while(temp->account_id != ptr->sacc)
			temp=temp->next;
			
			temp->balance=temp->balance + ptr->amt;
			
				Account	*temp1=a;
			while(temp1->account_id != ptr->tacc)
			temp1=temp1->next;
			
			temp1->balance=temp1->balance - ptr->amt;
printf("\nReverted Succesfully.\nThe remaining balance in account %d is %d\n and  account %d is %d\n\n",(ptr->sacc),temp->balance,(ptr->tacc),temp1->balance);
			}
			
		}
		break;

	}
}

void setInconsistent(Transaction* rlptr,int k)
{
	Transaction* ptr1=rlptr,*ptr2;
	int count=k,tid,found=0,count2;
	while((ptr1!=NULL)&&(count>0))
	{
		found=0;
		if(ptr1->operation==debit && ptr1->inb!=1)
		{
			ptr2=ptr1;
			count2=count-1;
			tid=ptr1->tid;
			while((ptr2!=NULL)&&(count2!=0)&&(found==0))
			{
				ptr2=ptr2->next;
				if(tid==ptr2->tid)
				{
					found=1;
				}
				count2--;
			}
			if(found==0)
				ptr1->incs=1;
			
		}
		ptr1=ptr1->next;
		count--;
	}
}

void revertInconsistent(Transaction* rlptr,int k,Account *a)
{
	Transaction* ptr=rlptr;
	Account *temp=a;
	int flag=0,c=k;
	while((ptr!=NULL)&&(k!=0))
	{
		if(ptr->incs==1)
		{
			printf("Inconsistency occured due to debiting from account %d without giving other sub-operations\n",(ptr->sacc));
				temp=a;
			while(temp->account_id != ptr->sacc)
			temp=temp->next;
			
			temp->balance=temp->balance + ptr->amt;
			
			printf("Removed Inconsistency Succesfully.\nThe remaining balance in account %d is %d\n\n",(ptr->sacc),temp->balance);
			flag=1;
			ptr->incs=0;
		}
		ptr=ptr->next;
		k--;
	}
	if(flag==0)
		printf("\nData is CONSISTENT\n");
}
void revertInconsistentFailure(Transaction* rlptr,int k,Account *a)
{
	Transaction* ptr=rlptr;
	Account *temp=a;
	int c=k;
	while((ptr!=NULL)&&(k!=0))
	{
		if(ptr->incs==1)
		{
			printf("Half done transaction reverted for account :%d\n",(ptr->sacc));
				temp=a;
			while(temp->account_id != ptr->sacc)
			temp=temp->next;
			
			temp->balance=temp->balance + ptr->amt;
			printf("The remaining balance in account %d is %d\n\n",(ptr->sacc),temp->balance);
			ptr->incs=0;
		}
		else
		{
			printmessage(ptr,a);
		}
		ptr=ptr->next;
		k--;
	}
}

Transaction* makeNodeCD(int choice,int saccno,int taccno,int amt,Transaction* lptr,Account *a)
{
	static int tid=1;
	Transaction* ptr,*rlptr;
	Transaction* retval;
	
		ptr=(Transaction*)malloc(sizeof(Transaction));
		ptr->operation=choice;
		ptr->amt=amt;
		ptr->pair1=0;
		ptr->pair2=0;
		ptr->inb=0;
		ptr->incs=0;
		ptr->time=getTime();
		if(choice==0)
		{
			ptr->tid=tid;
			ptr->sacc=saccno;
			ptr->tacc=taccno;
			tid++;
			retval=ptr;
		}
		else
		{
			int found_id=search(lptr,saccno,taccno,choice,amt,&(ptr->pair1),&(ptr->pair2));
			if(found_id==-1)
			{
				printf("Error invalid entry,data cannot be added\n");
				free(ptr);
				retval=NULL;
			}
			else
			{
				ptr->tid=found_id;
				ptr->sacc=saccno;
				ptr->tacc=taccno;
				retval=ptr;
			}
		}
	return retval;
}
Transaction* makeNode(int choice,int saccno,int taccno,int amt,Transaction* lptr,Account *a)
{
	static int length=0;
	static int tid=1;
	Transaction* ptr,*rlptr;
	Transaction* retval;
	if(choice==4)
	{
		rlptr=Reverse(lptr);
		setInconsistent(rlptr,length);
		revertInconsistentFailure(rlptr,length,a);
		Transaction *p=rlptr;//Deleting previous transactions
		while(rlptr!=NULL)
		{
			p=rlptr;
			rlptr=rlptr->next;
			free(p);
		}
		length=-1;
		retval=NULL;
	}
	else
	{
		ptr=(Transaction*)malloc(sizeof(Transaction));
		ptr->operation=choice;
		ptr->amt=amt;
		ptr->pair1=0;
		ptr->pair2=0;
		ptr->inb=0;
		ptr->incs=0;
		ptr->time=getTime();
		if(choice==0)
		{
			ptr->tid=tid;
			ptr->sacc=saccno;
			ptr->tacc=taccno;
			tid++;
			retval=ptr;
		}
		else
		{
			int found_id=search(lptr,saccno,taccno,choice,amt,&(ptr->pair1),&(ptr->pair2));
			if(found_id==-1)
			{
				printf("Error invalid entry,data cannot be added\n");
				free(ptr);
				retval=NULL;
			}
			else
			{
				ptr->tid=found_id;
				ptr->sacc=saccno;
				ptr->tacc=taccno;
				retval=ptr;
			}
		}
	}
	length++;
	return retval;
}



Transaction* inputTransaction(Transaction* lptr,int* length,Account *a)
{
	Transaction* ptr=lptr;
	int choice,k,i,amount,saccno,taccno;
	char ch='y';
	*length=0;
	while(ch=='y')
	{

		printf("Enter your choice for subtransactions:\n0.Debit\t1.Credit\n2.Abort\t3.Revert\t4.Failure\n");
		scanf("%d",&choice);
		if(choice!=4)
		{
			printf("Enter source account number\n");
			scanf("%d",&saccno);
			printf("Enter destination account number\n");
			scanf("%d",&taccno);
			printf("Enter amount\n");
			scanf("%d",&amount);
		}
		if((saccno>SIZE)||(saccno<0)||(taccno>SIZE)||(taccno<0)||(choice>4)||(choice<0))
			printf("Invalid entry (Account Number or Choice)\n");
		else
		{
			ptr=makeNode(choice,saccno,taccno,amount,lptr,a);
			if(ptr!=NULL)
			{
				ptr->next=lptr;
				lptr=ptr;
			}	
			else if((ptr==NULL)&&(choice==4))
			{
				lptr=NULL;
				*length=-1;
			}
			*length=*length+1;
		}
		printf("Do u want to continue (y/n)?\n");
		scanf("%c",&ch);
		scanf("%c",&ch);
		
	}
	//printf("Enter number of sub transactions to examine consistency\n");
	//scanf("%d",&k);
	return lptr;
}

Transaction* inputTransactionCreditandDebit(Transaction* lptr,Account *a,int *length)
{
	Transaction* ptr=lptr;
	int choice,k,i,amount,saccno,taccno;
	char ch='y';
	
	while(ch=='y')
	{
		printf("Enter your choice for subtransactions:\n0.Debit\t1.Credit\n");
		scanf("%d",&choice);
		printf("Enter source account number\n");
		scanf("%d",&saccno);
		printf("Enter destination account number\n");
		scanf("%d",&taccno);
		printf("Enter amount\n");
		scanf("%d",&amount);
		if((saccno>SIZE)||(saccno<0)||(taccno>SIZE)||(taccno<0)||(choice>1)||(choice<0))
			printf("Invalid entry (Account Number or Choice)\n");
		else
		{
			ptr=makeNodeCD(choice,saccno,taccno,amount,lptr,a);
			if(ptr!=NULL)
			{
				ptr->next=lptr;
				lptr=ptr;
				*length=*length+1;
			}
		}
		printf("Do u want to continue (y/n)?\n");
		scanf("%c",&ch);
		scanf("%c",&ch);
		
	}
	return lptr;
}

void printAccountDetails(Account *a)
{
	Account *ptr=a;
	while(ptr!=NULL)
	{
		printf("Account-ID=%d\n",ptr->account_id);
		printf("Account-Balance=%d\n\n",ptr->balance);
		ptr=ptr->next;
	}
}


void writeDataToFile(Account *a)
{
	Account *rev=ReverseA(a);
	FILE *fp;
	char str[50];
	fp=fopen("AccountDetails.txt","w");
	while(rev!=NULL)
	{
			fprintf(fp,"%d\n",rev->account_id);
			fprintf(fp,"%d\n",rev->balance);
			rev=rev->next;
		}
	fclose(fp);
}
	


int main()
{	
	int k,count,length=0,length1=0;
	char ch='y';
	Account *a=NULL;
	Transaction* lptr=NULL,*lptr2=NULL,*rlptr,*ptr;
	a=inputAccountDetails(a,&SIZE);
	// SHOWING ACCOUNTS BALANCE AND ID's
	printAccountDetails(a);
	lptr=inputTransactionCreditandDebit(lptr,a,&length1);
	printlist(lptr);
	rlptr=Reverse(lptr);
	printf("Enter value of 'k'\n");
	scanf("%d",&k);
	ptr=rlptr;
	count=k;
	while((count!=0)&&(ptr!=NULL))
	{
		printmessage(ptr,a);
		count--;
		ptr=ptr->next;
	}
	if(k>length1)
		count=length1;
	else
		count=k;
	ptr=rlptr;
	setInconsistent(ptr,count);
	ptr=rlptr;
	count=k;
	revertInconsistent(ptr,count,a);


	lptr2=inputTransaction(lptr2,&length,a);
	printlist(lptr2);
	count=length;
	rlptr=Reverse(lptr2);
	ptr=rlptr;
	while((count!=0) && (ptr!=NULL))
	{
		printmessage(ptr,a);
		count--;
		ptr=ptr->next;
	}
	ptr=rlptr;
	count=length;
	setInconsistent(ptr,count);
	ptr=rlptr;
	revertInconsistent(ptr,length,a);
	
	//WRITING DATA TO FILE
	writeDataToFile(a);
	return 0;	
}
