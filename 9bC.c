#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

void main(int c,char *v[])
{
	int n,i;
	void *psm;
	int shmid;
	shmid=shmget((key_t)1125,1024,0666);
	psm = shmat(shmid,NULL,0666);
	sscanf(v[1],"%d",&n);
	printf("[C] : Printing : \n");
	n = atoi(v[1]);
	for(i=1;i<2*n;i+=2)
	{
		sprintf(psm,"%d ",i);
		psm+=strlen(psm);
		printf("%d ",i);
	}
	printf("\n");
	sprintf(psm,"\n");
	shmctl(shmid,IPC_RMID,NULL);
}
