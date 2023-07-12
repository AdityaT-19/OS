#include<stdio.h>

struct Process
{
	int id,AT,BT,CT,TT,WT,RT,P;
};

typedef struct Process process;
typedef struct
{
    int id, time;
} Gantt;
Gantt g[10];
int gn = 0;
void printgantt()
{
    int i;
    printf("Gantt Chart\n");
    printf("_________________________________________________________________________________________\n");
    for (i = 1; i <= gn; i++)
        printf("\tP%d\t|", g[i].id);
    printf("\n---------------------------------------------------------------------------------------\n");
    for (i = 1; i <= gn; i++)
        printf("\t\t%d", g[i].time);
}
void Sort(process p[],int n,char c)
{
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-i-1;j++)
			if(c=='a'&&(p[j].AT>p[j+1].AT)||c=='i'&&(p[j].id>p[j+1].id)||c=='p'&&(p[j].P>p[j+1].P))
			{
				process temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
}

void calWT(process p[],int n)
{
	Sort(p,n,'p');
	int f=0,curT=0,num=n,pe=0,e=0,minp=9999;
	while(num>0)
	{
		for(int i=0;i<n;i++)
			if(p[i].AT<=curT&&p[i].P<minp&&p[i].RT>0)
			{
				minp=p[i].P;
				e=i;
				f=1;
			}
		if(f==0) curT++;
		else
		{
            if (pe != e)
            {
                g[gn].id = p[pe].id;
                g[gn++].time = curT;
            }
			p[e].RT--;
            pe=e;
			minp=p[e].P;
			if(p[e].RT==0)
			{
				p[e].CT=curT+1;
				p[e].TT=p[e].CT-p[e].AT;
				p[e].WT=p[e].TT-p[e].BT;
				num--;
				minp=9999;
			}
			curT++;
		}
	}	
    g[gn].id = p[pe].id;
    g[gn].time = curT;
}

void calAvgT(process p[],int n)
{
	calWT(p,n);
	printf("Process\tAT\tBT\tPv\tCT\tTT\tWT\n");
	int tWT=0,tTT=0;
	Sort(p,n,'i');
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].AT,p[i].BT,p[i].P,p[i].CT,p[i].TT,p[i].WT);
		tWT+=p[i].WT;
		tTT+=p[i].TT;
	}
	printf("Average WT : %.2f\n",(float)tWT/n);
	printf("Average TT : %.2f\n",(float)tTT/n);
}

void main()
{
	printf("Enter the number of process : ");
	int n;
	scanf("%d",&n);
	process p[n];
	for(int i =0 ;i<n;i++)
	{
		p[i].id=i+1;
		printf("Enter the AT, BT for the process %d: ",p[i].id);
		scanf("%d%d%d",&p[i].AT,&p[i].BT,&p[i].P);
		p[i].RT=p[i].BT;		
	}
	calAvgT(p,n);
    printgantt();
}
