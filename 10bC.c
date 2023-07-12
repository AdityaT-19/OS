#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/wait.h>

void main(int c,char *v[])
{
	int n,m,i;
	void *psm;
	int shmid;
	shmid=shm_open("A_OS",O_CREAT|O_RDWR,0666);
	ftruncate(shmid,1024);
	psm = mmap(0,1024,PROT_WRITE,MAP_SHARED,shmid,0);
	printf("[C] : Printing : \n");
	m = atoi(v[1]);
	n = atoi(v[2]);
	for(i=m;i<=n;i++)
	{
		int f=1;
		for(int j=2;j<=i/2;j++)
			if(i%j==0)
			{
				f=0;
				break;
			}
		if(f)
		{
			sprintf(psm,"%d ",i);
			printf("%d ",i);
			psm+=strlen(psm);
		}
	}
	printf("\n");
	sprintf(psm,"\n");
	shmctl(shmid,IPC_RMID,NULL);
}