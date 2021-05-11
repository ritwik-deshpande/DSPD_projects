#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
typedef struct vertex
{
	int source;
	int iedges;
}Vertex;
typedef struct List_Node_Tag
{
    int data;
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

List_Node *Make_Node(int data)
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

void Insert_Queue(Queue_type *qptr,int d)
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

void Delete_Queue(Queue_type *qptr,int *dptr)
{
    List_Node *ptr;
    if(!isQueueEmpty(qptr))
    {
        ptr=qptr->front;
        qptr->front=(qptr->front)->next;
        *dptr=ptr->data;
        free(ptr);
        if (qptr->front==NULL)
        {
            qptr->rear=NULL;
        }
    }
}
void topo(Vertex v[],Queue_type* qptr)
{
	int i=0,j;
	Initialise(qptr);
	for(i=0;i<SIZE;i++)
	{
		if(v[i].iedges==0)
		{
			Insert_Queue(qptr,i);
		}
	}
	i=0;
	while((!isQueueEmpty(qptr))&&(i<SIZE))
	{
		int d;
		Delete_Queue(qptr,&d);
		printf("%d\t",d);
		for(j=0;j<SIZE;j++)
		{
			if(d==v[j].source)
			{
				v[j].iedges--;
				if(v[j].iedges==0)
					Insert_Queue(qptr,j);
			}
			
		}
		i++;
	}
	if(i<SIZE)
		printf("Cycle exists!!!\n");
}
int main()
{
	Vertex v[SIZE];
	int v1=0,v2=0,i;
	for(i=0;i<SIZE;i++)
	{
		v[i].iedges=0;
	}
	while(v1!=-1 && v2!=-1)
	{
		printf("Enter vertex source to destination\n");
		scanf("%d%d",&v1,&v2);
		if(v2!=-1 &&  v1!=-1)
		{
			v[v2].source=v1;
			v[v2].iedges++;
		}
	}
	Queue_type qptr;
	topo(v,&qptr);
	return 0;
}

