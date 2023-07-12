#include <stdio.h>
typedef struct
{
    int id, at, bt, ct, tat, wt, rt;
} Process;

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
    for (i = 0; i < gn; i++)
        printf("\tP%d\t|", g[i].id);
    printf("\n---------------------------------------------------------------------------------------\n");
    for (i = 0; i < gn; i++)
        printf("\t\t%d", g[i].time);
}

void Sort(Process p[],int n,char c)
{
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-i-1;j++)
			if(c=='i'&&(p[j].id>p[j+1].id)||c=='b'&&(p[j].bt>p[j+1].bt))
			{
				Process temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
}

void sjfscheduling(Process proc[], int n)
{
    int i, f = 0, time = 0, exec, num = n;
    Sort(proc, n,'i');
    while (num > 0)
    {
        f = 0;
        exec = n - 1;
        for (i = 0; i < n; i++)
        {
            if (proc[i].rt > 0 && proc[i].at <= time)
            {
                exec = i;
                f = 1;
                break;
            }
        }
        if (f == 0)
            time++;
        else
        {
            time += proc[exec].bt;
            proc[exec].ct = time;
            proc[exec].tat = proc[exec].ct - proc[exec].at;
            proc[exec].wt = proc[exec].tat - proc[exec].bt;
            proc[exec].rt = 0;
            g[gn].id = proc[i].id;
		    g[gn++].time = time;
            num--;
        }
    }
}
void printdata(Process processes[], int n)
{
    int wtsum = 0, tatsum = 0;
    Sort(processes,n,'i');
    printf("P-ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        wtsum += processes[i].wt;
        tatsum += processes[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }
    printf("Average Waiting Time : %.2f\n", (float)wtsum / n);
    printf("Average Turnaround Time : %.2f\n", (float)tatsum / n);
}
void main()
{
    printf("Enter the number of process : ");
	int n;
	scanf("%d",&n);
	Process p[n];
	for(int i =0 ;i<n;i++)
	{
		p[i].id=i+1;
		printf("Enter the AT and BT for the process %d: ",p[i].id);
		scanf("%d%d",&p[i].at,&p[i].bt);		
	}
    sjfscheduling(p,n);
    printdata(p, n);
    printgantt();
}