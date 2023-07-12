#include<stdio.h>

struct Process
{
	int id,AT,BT,CT,TT,WT,RT;
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
			if(c=='i'&&(p[j].id>p[j+1].id)||c=='b'&&(p[j].BT>p[j+1].BT))
			{
				process temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
}

void calWT(process p[],int n)
{
	Sort(p,n,'b');
	int f=0,curT=0,num=n,pe=0,e=0,mint=9999;
	while(num>0)
	{
		for(int i=0;i<n;i++)
			if(p[i].AT<=curT&&p[i].RT<mint&&p[i].RT>0)
			{
				mint=p[i].RT;
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
			mint=p[e].RT;
			curT++;
			if(mint==0)
				mint=9999;
			if(p[e].RT==0)
			{
				p[e].CT=curT;
				p[e].TT=p[e].CT-p[e].AT;
				p[e].WT=p[e].TT-p[e].BT;
				num--;
			}
			

           
		}
	}	
    g[gn].id = p[pe].id;
    g[gn].time = curT;
}

void calAvgT(process p[],int n)
{
	calWT(p,n);
	printf("Process\tAT\tBT\tCT\tTT\tWT\n");
	int tWT=0,tTT=0;
	Sort(p,n,'i');
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].AT,p[i].BT,p[i].CT,p[i].TT,p[i].WT);
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
		printf("Enter the AT and BT for the process %d: ",p[i].id);
		scanf("%d%d",&p[i].AT,&p[i].BT);
		p[i].RT=p[i].BT;		
	}
	calAvgT(p,n);
        printgantt();
}
