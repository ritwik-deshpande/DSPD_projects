#include<stdio.h>
#define SIZE 100
#define SUCCESS 1
#define FAILURE 0
struct date
{
	int day;
	int month;
	int year;
};
struct comp_specs
{
	int key;
	struct date warranty_period;
	struct date doM;
	struct date doP;
	struct date lifeperiod;
	struct date writeoffdate;
    int pro;
};
struct proc
{
    int i3;
    int i5;
    int i7;
};
struct event
{
	struct comp_specs data;
	int event;
};
int insert(struct comp_specs data[],struct comp_specs d1,int size)
{
    int found=0;
    int status=SUCCESS;
    int i=0;
    while((i<size)&&(found==0))
    {
        if(data[i].key==d1.key)
            found=1;
        i++;
    }
    /* Updating the list*/
    if(found)
    {
	i--;
        data[i]=d1;
	status=2;
    }
    else
    {
        int i=0,free_index=0;
        while((i<SIZE)&&(free_index==0))
        {
            if(data[i].key==0)
                free_index=1;
            else
                i++;
        }
        if(free_index)
        {
        	data[i]=d1;
        }
        else
        {
            status=FAILURE;
        }
    }
    return status;
}
/*Finding leap year*/
int isleapyear(int year)
{
	int retval;
	if(year%4==0)
	{
		if(year%100==0)
		{
			if(year%400==0)
				retval=1;
			else
				retval=0;
		}
		else
			retval=1;
	}
	else
	{
		retval=0;
	}
	return retval;
}
/*Finding Time period between 2 dates in days*/
int subdate(struct date d1,struct date d2)
{
    int i,totaldays=0,d,t=0,j;
    for(j=d1.month;j<=12;j++)
    {
        switch(j)
        {
		case 1:
	    	{
		    if(t==0)
		    {
		        totaldays=31-d1.day;
		        t=1;
		    }
		    else
		        totaldays=totaldays+31;
		}
		case 2:
		{
			if(isleapyear(d1.year))
			{
			    if(t==0)
			    {
				totaldays=29-d1.day;
				t=1;
			     }
            		     else
				totaldays=totaldays+29;
			}
			else
			{
			    if(t==0)
			    {
				totaldays=28-d1.day;
				t=1;
			    }
            		    else
				totaldays=totaldays+28;
			}
		}
		case 3:
		{
		    if(t==0)
            	    {
		        totaldays=31-d1.day;
		        t=1;	
            	    }
           	    else
			totaldays=totaldays+31;
		}
		case 4:
		{
		    if(t==0)
            	    {
		        totaldays=30-d1.day;
		        t=1;
           	    }
            	    else
			totaldays=totaldays+30;
		}
		case 5:
		{
		    if(t==0)
            	    {
		        totaldays=31-d1.day;
		        t=1;
            		}
            	     else
			totaldays=totaldays+31;
		}
		case 6:
		{
		    if(t==0)
		    {
		        totaldays=30-d1.day;
		        t=1;
		    }
            	    else
			totaldays=totaldays+30;
		}
		case 7:
		{
		    if(t==0)
            	    {
		        totaldays=31-d1.day;
		        t=1;
            	    }
            	    else
			totaldays=totaldays+31;
		}
		case 8:
		{
		    if(t==0)
            	    {
		        totaldays=31-d1.day;
		        t=1;
            	    }
            	    else
			totaldays=totaldays+31;
		}
		case 9:
		{
		    if(t==0)
            	    {
		        totaldays=30-d1.day;
		        t=1;
		    }
		    else
			totaldays=totaldays+30;
		}
		case 10:
		{
		    if(t==0)
            	    {
		        totaldays=31-d1.day;
		        t=1;
		    }
		    else
			totaldays=totaldays+31;
		}
		case 11:
		{
		    if(t==0)
		    {
		        totaldays=30-d1.day;
		        t=1;
		    }
            	    else
			totaldays=totaldays+30;
		}
		case 12:
		{
		    if(t==0)
		    {
		        totaldays=31-d1.day;
		        t=1;
		    }
            	    else
			totaldays=totaldays+31;
		}
    }
    for(j=1;j<d2.month;j++)
    {
        switch(j)
        {
		case 1:
		{
			totaldays=totaldays+31;
		}
		case 2:
		{
			if(isleapyear(d1.year))
			{
				totaldays=totaldays+29;
			}
			else
			{
				totaldays=totaldays+28;
			}
		}
		case 3:
		{
			totaldays=totaldays+31;
		}
		case 4:
		{
			totaldays=totaldays+30;
		}
		case 5:
		{
			totaldays=totaldays+31;
		}
		case 6:
		{
			totaldays=totaldays+30;
		}
		case 7:
		{
			totaldays=totaldays+31;
		}
		case 8:
		{
			totaldays=totaldays+31;
		}
		case 9:
		{
			totaldays=totaldays+30;
		}
		case 10:
		{
			totaldays=totaldays+31;
		}
		case 11:
		{
			totaldays=totaldays+30;
		}
		case 12:
		{
			totaldays=totaldays+31;
		}
    }
    }
    for(i=d1.year+1;i<=d2.year-1;i++)
    {
        if(isleapyear(i))
        {
            totaldays=totaldays+366;
        }
        else
        {
            totaldays=totaldays+365;
        }
    }
    totaldays=totaldays+d2.day;
    return totaldays;
    }
}
/*Differnce of writeoffdate and Date of purchase*/
void getLongestUsedPeriod(struct comp_specs data[],int size)
{
    int i=0,max2,max=0,k=0,pos[SIZE],j=0;
    for(i=0;i<size;i++)
    {
        max2=subdate(data[i].doP,data[i].writeoffdate);
        if(max<max2)
	{
	    k=0;
	    pos[k]=i;
            max=max2;
	    k=1;
	}
	else if(max==max2)
	{
		pos[k]=i;
		k++;
	}
    }
    for(j=0;j<k;j++)
    {
		i=pos[j];
		printf("ID:%d\n",data[i].key);
		printf("Date of Manufacture:%d/%d/%d\n",data[i].doM.day,data[i].doM.month,data[i].doM.year);
		printf("Date of Purchase:%d/%d/%d\n",data[i].doP.day,data[i].doP.month,data[i].doP.year);
		printf("Warranty:%d/%d/%d\n",data[i].warranty_period.day,data[i].warranty_period.month,data[i].warranty_period.year);
		printf("Write off date:%d/%d/%d\n",data[i].writeoffdate.day,data[i].writeoffdate.month,data[i].writeoffdate.year);
		printf("Lifeperiod:%d/%d/%d\n",data[i].lifeperiod.day,data[i].lifeperiod.month,data[i].lifeperiod.year);
		printf("Processor level isI%d\n",data[i].pro);
    }
	
}
/*addition of 2 dates*/
struct date adddate(struct date m,struct date n)
{
	struct date d;
	d.day=0;
	d.month=0;
	d.year=0;
	d.year=m.year+n.year;
	d.month=m.month+n.month;
	if(d.month>12)
	{
		d.month=d.month-12;
		d.year++;
	}
	d.day=m.day+n.day;
	switch(d.month)
	{
		case 1:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
		case 2:
		{
			if(isleapyear(d.year))
			{
				if(d.day>29)
					d.day=d.day-29;
			}
			else
			{
				if(d.day>28)
					d.day=d.day-28;
			}
		}
		case 3:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
		case 4:
		{
			if(d.day>30)
				d.day=d.day-30;
		}
		case 5:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
		case 6:
		{
			if(d.day>30)
				d.day=d.day-30;
		}
		case 7:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
		case 8:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
		case 9:
		{
			if(d.day>30)
				d.day=d.day-30;
		}
		case 10:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
		case 11:
		{
			if(d.day>30)
				d.day=d.day-30;
		}
		case 12:
		{
			if(d.day>31)
				d.day=d.day-31;
		}
	}
	return d;
}
/*To delete given data*/
void delete(struct comp_specs data[],int size,int a)
{
	struct date k;
	k.day=0;
	k.month=0;
	k.year=0;
	struct comp_specs d;
	    d.key=0;
        d.doP=k;
        d.doM=k;
        d.warranty_period=k;
        d.lifeperiod=k;
        d.writeoffdate=k;
        d.pro=0;

	    int found=0,pos=0;
	    int status=SUCCESS;
	    int i=0;
	    for(i=a;i<size-1;i++)
		data[i]=data[i+1];

	    data[size-1]=d;
    
}
/*Function to take date from user*/
struct date getdate()
{
    struct date d;
    printf("Enter day\n");
    scanf("%d",&d.day);
    printf("Enter month\n");
    scanf("%d",&d.month);
    printf("Enter year\n");
    scanf("%d",&d.year);
    return d;

}
/*Function to get computer specs from user*/
void getdata(struct comp_specs data[],int size)
{
	int i;
   	for(i=0;i<size;i++)
	{
        printf("Enter the computer ID\n");
	scanf("%d",&data[i].key);
	printf("Enter the warranty period\n");
	data[i].warranty_period=getdate();
        printf("Enter Date of Manufacture\n");
        data[i].doM=getdate();
        printf("Enter Date of Purchase\n");
        data[i].doP=getdate();
        printf("Enter life period\n");
        data[i].lifeperiod=getdate();
        printf("Enter processor level\n");
        scanf("%d",&data[i].pro);
	data[i].writeoffdate=adddate(data[i].doM,data[i].lifeperiod);
	}
}
/*initialize database to zero*/
void initialize(struct comp_specs data[])
{
    int i;
	struct date d;
	d.day=0;
        d.month=0;
    	d.year=0;
	for(i=0;i<SIZE;i++)
	{
        data[i].key=0;
        data[i].doP=d;
        data[i].doM=d;
        data[i].warranty_period=d;
        data[i].lifeperiod=d;
        data[i].writeoffdate=d;
        data[i].pro=0;

	}
}
/*Print database*/
void printlist(struct comp_specs data[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("ID:%d\n",data[i].key);
		printf("Date of Manufacture:%d/%d/%d\n",data[i].doM.day,data[i].doM.month,data[i].doM.year);
		printf("Date of Purchase:%d/%d/%d\n",data[i].doP.day,data[i].doP.month,data[i].doP.year);
		printf("Warranty:%d/%d/%d\n",data[i].warranty_period.day,data[i].warranty_period.month,data[i].warranty_period.year);
		printf("Write off date:%d/%d/%d\n",data[i].writeoffdate.day,data[i].writeoffdate.month,data[i].writeoffdate.year);
		printf("Lifeperiod:%d/%d/%d\n",data[i].lifeperiod.day,data[i].lifeperiod.month,data[i].lifeperiod.year);
		printf("Processor level is:I%d\n",data[i].pro);
	}
}
/*comparison of dates*/
int comparedate(struct date m,struct date n)
{
        if(m.year>n.year)
            return 1;
        if(m.year<n.year)
            return 0;
        if(m.year==n.year)
        {
            if(m.month>n.month)
                return 1;
            if(m.month<n.month)
                return 0;
            if(m.month==n.month)
            {
                if(m.day>n.day)
                    return 1;
                if(m.day<n.day)
                    return 0;
                if(m.day==n.day)
                    return 2;
            }
        }
}
void getSortedOnDateOfPurchase(struct comp_specs data[],struct comp_specs data1[],int size)
{
    int i,j,temp,sorted=0;
    struct comp_specs t;
	for(i=0;i<size;i++)
	{
	data1[i]=data[i];
	}
    for(i=0;(i<size-1) && (sorted==0);i++)
    {
        sorted=1;
        for(j=0;j<size-i-1;j++)
        {
            if(comparedate(data1[j].doP,data1[j+1].doP)==1)
            {
                t=data1[j];
                data1[j]=data1[j+1];
                data1[j+1]=t;

            }
        }
    }
}
/*Warranty period + date of purchase to give expiry*/
void getSortedOnWarrantyPeriodExpiry(struct comp_specs data[],struct comp_specs data1[],int size)
{
    struct comp_specs t;
    int i,j,temp,sorted=0;
	for(i=0;i<size;i++)
	{
	data1[i]=data[i];
	}
    for(i=0;(i<size-1) && (sorted==0);i++)
    {
        sorted=1;
        for(j=0;j<size-i-1;j++)
        {
            if(comparedate(adddate(data1[j].warranty_period,data1[j].doP),adddate(data1[j+1].doP,data1[j+1].warranty_period))==1)
            {
                t=data1[j];
                data1[j]=data1[j+1];
                data1[j+1]=t;
            }
        }
    }
}
void getSortedOnUsedPeriod(struct comp_specs data[],struct comp_specs data1[],int size)
{
    struct comp_specs t;
    int i,j,temp,sorted=0;
    for(i=0;i<size;i++)
    {
     data1[i]=data[i];
    }
    for(i=0;(i<size-1) && (sorted==0);i++)
    {
        sorted=1;
        for(j=0;j<size-i-1;j++)
        {
            if(subdate(data1[j].writeoffdate,data1[j].doP)>subdate(data1[j+1].writeoffdate,data1[j+1].doP))
            {
                t=data1[j];
                data1[j]=data1[j+1];
                data1[j+1]=t;
            }
        }
    }
}
void listUnion(struct comp_specs l1[],struct comp_specs l2[],struct comp_specs l3[],int m,int n)
{
	int i=0,j=0,k=0;
	while((i<m)&&(j<n))
	{
		if(comparedate(l1[i].doP,l2[j].doP)==0)
		{
			l3[k++]=l1[i++];
		}
		if(comparedate(l1[i].doP,l2[j].doP)==1)
		{
			l3[k++]=l2[j++];
		}
		if(comparedate(l1[i].doP,l2[j].doP)==2)
		{
			if(l1[i].key>l2[j].key)
			{
				l3[k++]=l2[j++];
			}
			if(l1[i].key<l2[j].key)
			{
				l3[k++]=l1[i++];
			}
			if(l1[i].key==l2[j].key)
			{
				l3[k++]=l1[i++];
				j++;
			}
		}
	}
	while(i<m)
	{
		l3[k++]=l1[i++];
	}
	while(j<n)
	{
		l3[k++]=l2[j++];
	}
	printlist(l3,k);
}
void listIntersection(struct comp_specs q1[],struct comp_specs q2[],struct comp_specs q3[],int m,int n)
{
	int i=0,j=0,k=0;
	while((i<n)&&(j<m))
	{
		if(comparedate(q1[i].doP,q2[j].doP)==2)
		{
			if(q1[i].key==q2[j].key)
			{
				if(q1[i].pro>q2[j].pro)
				{
					q3[k++]=q1[i++];
					j++;
				}
				if(q1[i].pro<q2[j].pro)
				{
					q3[k++]=q2[j++];
					i++;
				}
				if(q1[i].pro==q2[j].pro)
				{
					q3[k++]=q1[i++];
					j++;
				}
			}
			else if(q1[i].key<q2[j].key)
			{
				i++;
			}
			else
			{
				j++;
			}
		}
		else if(comparedate(q1[i].doP,q2[j].doP)==1)
		{
			j++;
		}
		else
		{
			i++;
		}	
	}
	printlist(q3,k);
}
void listDifference(struct comp_specs r1[],struct comp_specs r2[],struct comp_specs r3[],int m,int n)
{
	int i=0,j=0,k=0;
	int count;
	while((i<m)&&(j<n))
	{
		if((comparedate(r1[i].doP,r2[j].doP)==2)&&(r1[i].key==r2[j].key))
		{
			i++;
			j++;
		}
		else
		{
			r3[k++]=r1[i++];
		}
	}	
	while(i<m)
	{
		r3[k++]=r1[i++];
	}
	printlist(r3,k);
}
void listSymmetricDifference(struct comp_specs p1[],struct comp_specs p2[],struct comp_specs p3[],int m,int n)
{
	int i=0,j=0,k=0;
	while((i<m)&&(j<n))
	{
		if(comparedate(p1[i].doP,p2[j].doP)==0)
		{
			p3[k++]=p1[i++];
		}
		if(comparedate(p1[i].doP,p2[j].doP)==1)
		{
			p3[k++]=p2[j++];
		}
		if(comparedate(p1[i].doP,p2[j].doP)==2)
		{
			if(p1[i].key>p2[j].key)
			{
				p3[k++]=p2[j++];
			}
			if(p1[i].key<p2[j].key)
			{
				p3[k++]=p1[i++];
			}
			if(p1[i].key==p2[j].key)
			{
				i++;
				j++;
			}
		}
	}
	while(i<m)
	{
	p3[k++]=p1[i++];
	}
	while(j<n)
	{
	p3[k++]=p2[j++];
	}
	printlist(p3,k);
}
void sort(struct comp_specs data[],int size)
{
    int i,j,temp,sorted=0;
    struct comp_specs t;
    for(i=0;(i<size-1) && (sorted==0);i++)
    {
        sorted=1;
        for(j=0;j<SIZE-i-1;j++)
        {
            if(comparedate(data[i].doP,data[i+1].doP)==1)
            {
                t=data[i];
                data[i]=data[i+1];
                data[i+1]=t;
            }
            else if(comparedate(data[i].doP,data[i+1].doP)==2)
            {
                if(data[i].key>data[i+1].key)
                {
                t=data[i];
                data[i]=data[i+1];
                data[i+1]=t;
            	}
            }
        }
    }
}
/* To check whether user has filled date of purchase*/
int checkDate(struct date m)
{
	if(m.day==0 && m.year==0 && m.month==0)
		return 0;
	else
		return 1;
}
int isEmpty(struct comp_specs m[])
{
	int t=1;
	int i;

	for(i=0;i<SIZE && t==1;i++)
	{
		if(m[i].key!=0 && checkDate(m[i].doP)==1)
			t=0;
	}
	
	return t;
}
int isFull(struct comp_specs m[])
{
	int t=1;
	int i;

	for(i=0;(i<SIZE && t==1);i++)
	{
		if(m[i].key==0 && checkDate(m[i].doP)==0)
		t=0;
	}
	return t;
}
struct proc getNumComputers(struct comp_specs m[],int size)
{
	struct proc p;
	p.i3=0;
	p.i5=0;
	p.i7=0;

	int i=0;
	for(i=0;i<size;i++)
	{
		if(m[i].pro==3)
		p.i3++;
		if(m[i].pro==5)
		p.i5++;
		if(m[i].pro==7)
		p.i7++;

	}
	return p;
}
void sortwithkey(struct comp_specs data[],int size)
{
    int i,j,temp,sorted=0;
    struct comp_specs t;
    for(i=0;(i<size-1) && (sorted==0);i++)
    {
        sorted=1;
        for(j=0;j<size-i-1;j++)
        {
      
                if(data[j].key>data[j+1].key)
                {
                t=data[j];
                data[j]=data[j+1];
                data[j+1]=t;
            	}
            
        }
    }
}
int remove_duplicates(struct comp_specs data[],int size)
{
        int i=0;
        sortwithkey(data,size);
        while(i<size-1)
        {
           if(data[i].key==data[i+1].key)
           {
               if(data[i].pro>data[i+1].pro)
               {
                    delete(data,size,i+1);
		    size--;
                    i=0;
               }
                else
                {
                    delete(data,size,i);
		    size--;
                    i=0;
                }
           }
           i++;
        }
	return size;
}
/*
void getlists()
{
	struct comp_specs data[SIZE];
	int size,size1,size2,i;
	initialize(data);
	printf("Pls enter no of entries\n");
	scanf("%d",&size);
	getdata(data,size);
	for(i=0;i<size;i++)
	{
		data[i].writeoffdate=adddate(data[i].doM,data[i].lifeperiod);
	}
	sort(data,size);
	struct comp_specs data1[SIZE];
	initialize(data1);
	printf("Pls enter no of entries\n");
	scanf("%d",&size1);
	getdata(data1,size1);
	for(i=0;i<size1;i++)
	{
		data1[i].writeoffdate=adddate(data1[i].doM,data1[i].lifeperiod);
	}
	sort(data1,size1);
	struct comp_specs data2[SIZE];
	initialize(data2);
	listSymmetricDifference(data,data1,data2,size,size1);
}
*/
/*Search element based on key*/
int search(struct comp_specs data[],int key,struct date d,int size)
{
	int i,retval=-1;
	for(i=0;i<size;i++)
	{
		if((data[i].key==key)&&(comparedate(data[i].doP,d)==2))
			retval=i;
	}
	return retval;
}
void Updatelists(struct comp_specs data[],struct event e[],int size)
{
	int j,i;
	int ch=1;
	printf("\n Enter your choices \n1.Increase lifeperiod \n2.Purchase \n3.Sell \n4.Upgrade processor\n For each computer\n");
	for(j=0;j<SIZE && ch==1;j++)
	{
		printf("For computer %d Enter Id and date of purchase (day month year)\n",j+1);
		scanf("%d%d%d%d",&e[j].data.key,&e[j].data.doP.day,&e[j].data.doP.month,&e[j].data.doP.year);
		printf("Enter event no:");
		scanf("%d",&e[j].event);
		printf("Do u want to continue(y=1/n=0)?\n");
		scanf("%d",&ch);
	}
	for(i=0;i<j;i++)
	{
		switch(e[i].event)
		{
			case 1:
			{
				int a;
				struct date d;
				printf("Enter the amount by which you want to increase the life period as date(day month year)\n");
				scanf("%d%d%d",&d.day,&d.month,&d.year);
				a=search(data,e[i].data.key,e[i].data.doP,size);
				if(a!=-1)
					data[a].lifeperiod=adddate(d,data[a].lifeperiod);
				else
					printf("Data not found invalid Key\n");
				break;
			}
			case 2:
			{	
				int a;
				a=search(data,e[i].data.key,e[i].data.doP,size);
				if(a==-1)
				{
					printf("Enter data to be inserted\n");
					printf("Enter the warranty period\n");
					e[i].data.warranty_period=getdate();
					printf("Enter Date of Manufacture\n");
					e[i].data.doM=getdate();
					printf("Enter life period\n");
					e[i].data.lifeperiod=getdate();
					printf("Enter processor level\n");
					scanf("%d",&e[i].data.pro);
					e[i].data.writeoffdate=adddate(e[i].data.doM,e[i].data.lifeperiod);
					insert(data,e[i].data,size);
					size++;
				}
				else
					printf("Already purchased\n");
				break;
			}
			case 3:
			{
				int a;
				a=search(data,e[i].data.key,e[i].data.doP,size);
				if(a!=-1)
				{
					delete(data,size,a);
					printf("Deleted Successfully");
					size--;
				}
				else
					printf("Data does not exist\n");
				
				break;
			}
			case 4:
			{
				int a,n;
				a=search(data,e[i].data.key,e[i].data.doP,size);
				if(a!=-1)
				{
					if(data[a].pro!=7)
					{
						printf("Enter processor generation to be upgraded\n");
						scanf("%d",&n);
						data[a].pro=n;
					}
				}
				else
					printf("Data does not exist\n");
				
				break;
			}
			default:
			{
				printf("Invalid event");
				
			}
		}	
	}
	printlist(data,size);
	
}
/*Function to segregate according to different processor level*/
void segregate(struct comp_specs data[],struct comp_specs l1[],struct comp_specs l2[],struct comp_specs l3[],int size)
{
	int i=0,k=0,j=0,m=0;
	while(i<size)
	{
		if(data[i].pro==3)
			l1[k++]=data[i++];
		if(data[i].pro==5)
			l2[j++]=data[i++];
		if(data[i].pro==7)
			l3[m++]=data[i++];
	}
	printf("Contents with I3 processor\n");
	printlist(l1,k);
	printf("Contents with I5 processor\n");
	printlist(l2,j);
	printf("Contents with I7 processor\n");
	printlist(l3,m);
}
int main()
{
	int i=0;
	int ch=1;
	int status,size;
	int f;
	struct comp_specs data[SIZE];
	printf("Enter no of entries\n");
	scanf("%d",&size);
	getdata(data,size);
	while(ch==1)
	{
	printf("MENU\n");
	printf("Enter your choice number\n");
	printf("1.INSERT\n");
	printf("2.DELETE\n");
	printf("3.getNumComputers\n");
	printf("4.isEmpty\n");
	printf("5.isFull\n");
	printf("6.getLongestUsedPeriod\n");
	printf("7.UpdateLists\n");
	printf("8.getSortedOnDateOfPurchase\n");
	printf("9.getSortedOnWarrantyPeriodExpiry\n");
	printf("10.getSortedOnUsedPeriod\n");
	printf("11.remove_duplicates\n");
	printf("12.List Functions\n");
	printf("13.Segregate List\n");
	printf("14.Print original record\n");
	printf("Enter your choice:\n");
	scanf("%d",&f);
	switch(f)
	{
		case 1:
		{
			struct comp_specs d;
			printf("Enter data to be inserted\n");
			printf("Enter the computer ID\n");
			scanf("%d",&d.key);
			printf("Enter the warranty period\n");
			d.warranty_period=getdate();
			printf("Enter Date of Manufacture\n");
			d.doM=getdate();
			printf("Enter Date of Purchase\n");
			d.doP=getdate();
			printf("Enter life period\n");
			d.lifeperiod=getdate();
			printf("Enter processor level\n");
			scanf("%d",&d.pro);
			d.writeoffdate=adddate(d.doM,d.lifeperiod);
			if(insert(data,d,size)==1)
			{
				size++;
				printf("Insert is Successful!!\n");
			}
			else if(insert(data,d,size)==2)
			{
				printf("Updation is Successful!!\n");
			}
			else
			{
				printf("Insert is Unsuccessful!!\n");
			}
			sort(data,size);
			printlist(data,size);
			break;
		}
		case 2:
		{
			struct comp_specs d;
			printf("Enter keys of data to be deleted\n");
			printf("Enter the computer ID\n");
			scanf("%d",&d.key);
			printf("Enter Date of Purchase\n");
			d.doP=getdate();
			int a;
			a=search(data,d.key,d.doP,size);
			if(a!=-1)
			{
			delete(data,size,a);
			size--;
			}
			else
				printf("Record not found\n");
			sort(data,size);
			printlist(data,size);
			break;
		}
		case 3:
		{	
			struct proc p;
			p=getNumComputers(data,size);
			printf("The no. of 3rd generation computers are:%d\n",p.i3);
			printf("The no. of 5th generation computers are:%d\n",p.i5);
			printf("The no. of 7th generation computers are:%d\n",p.i7);
			break;
		}
		case 4:
		{
			int a=isEmpty(data);
			if(a==1)
			printf("The List is Empty\n");
			else
			printf("The list is not Empty\n");
			break;
		}
		case 5:
		{
			int a=isFull(data);
			if(a==1)
			printf("The List is Full\n");
			else
			printf("The list is not Full\n");
			break;
		}
		case 6:
		{
			getLongestUsedPeriod(data,size);
			break;
		}
		case 7:
		{
			struct event e[SIZE];
			Updatelists(data,e,size);
			break;
		}
		case 8:
		{
			struct comp_specs data1[SIZE];
			initialize(data1);
			getSortedOnDateOfPurchase(data,data1,size);
			printlist(data1,size);
			break;
		}
		case 9:
		{
			struct comp_specs data1[SIZE];
			getSortedOnWarrantyPeriodExpiry(data,data1,size);
			printlist(data1,size);
			break;
		}
		case 10:
		{
			struct comp_specs data1[SIZE];
			getSortedOnUsedPeriod(data,data1,size);
			printlist(data1,size);
			break;
		}
		case 11:
		{
			int size2,i;
			printf("Enter no of entries\n");
			scanf("%d",&size2);
			struct comp_specs data2[size2];
			printf("Enter data to be inserted\n");
			for(i=0;i<size2;i++)	
			{
			printf("Enter the computer ID\n");
			scanf("%d",&data2[i].key);
			printf("Enter the warranty period\n");
			data2[i].warranty_period=getdate();
			printf("Enter Date of Manufacture\n");
			data2[i].doM=getdate();
			printf("Enter Date of Purchase\n");
			data2[i].doP=getdate();
			printf("Enter life period\n");
			data2[i].lifeperiod=getdate();
			printf("Enter processor level\n");
			scanf("%d",&data2[i].pro);
			data2[i].writeoffdate=adddate(data2[i].doM,data2[i].lifeperiod);
			}
			size2=remove_duplicates(data2,size2);
			sort(data2,size2);
			printlist(data2,size2);
			break;
		}
		case 12:
		{
		printf("Enter List\n");
		int size9,i;
			printf("Enter no of entries\n");
			scanf("%d",&size9);
			struct comp_specs data9[size9];
			printf("Enter data to be inserted\n");
			for(i=0;i<size9;i++)	
			{
			printf("Enter the computer ID\n");
			scanf("%d",&data9[i].key);
			printf("Enter the warranty period\n");
			data9[i].warranty_period=getdate();
			printf("Enter Date of Manufacture\n");
			data9[i].doM=getdate();
			printf("Enter Date of Purchase\n");
			data9[i].doP=getdate();
			printf("Enter life period\n");
			data9[i].lifeperiod=getdate();
			printf("Enter processor level\n");
			scanf("%d",&data9[i].pro);
			data9[i].writeoffdate=adddate(data9[i].doM,data9[i].lifeperiod);
			}
		size9=remove_duplicates(data9,size9);
		size=remove_duplicates(data,size);
		int as;
		int c1=1;
		while(c1==1)
		{
		printf("Enter the No. of the function to be performed\n");
		printf("1.LIST UNION\n2.LIST INTERSECTION\n3.LIST DIFFERENCE\n4.LIST SYMMETRIC DIFFERENCE\n");
		scanf("%d",&as);
		switch(as)
		{
			case 1:
			{
				struct comp_specs d1[SIZE];
				sort(data,size);
				sort(data9,size9);
				listUnion(data,data9,d1,size,size9);
				break;
			}
			case 2:
			{
				struct comp_specs d2[SIZE];
				sort(data,size);
				sort(data9,size9);
				listIntersection(data,data9,d2,size,size9);
				break;
			}
			case 3:
			{
				struct comp_specs d3[SIZE];
				sort(data,size);
				sort(data9,size9);
				listDifference(data,data9,d3,size,size9);
				break;
			}
			case 4:
			{
				struct comp_specs d4[SIZE];
				sort(data,size);
				sort(data9,size9);
				listSymmetricDifference(data,data9,d4,size,size9);
				break;
			}
			default:
			{
				printf("Invalid Choice\n");
				break;
			}
		}
		printf("Do u wish to continue with list functions(y=1/n=0)?");
		scanf("%d",&c1);
		}
		break;
		}
		case 13:
		{
			struct comp_specs l1[SIZE];
			struct comp_specs l2[SIZE];
			struct comp_specs l3[SIZE];
			segregate(data,l1,l2,l3,size);
			break;
		}
		case 14:
		{
			printlist(data,size);
			break;
		}	
		default:
		{
			printf("Invalid option\n");
		}
	}
	printf("Do u wish to continue(y=1/n=0)?\n");
	scanf("%d",&ch);
	}
	return 0;
}
