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
	int n,n1,n2,n3,i;
	void *psm;
	int shmid;
	shmid=shm_open("A_OS",O_CREAT|O_RDWR,0666);
	ftruncate(shmid,1024);
	psm = mmap(0,1024,PROT_WRITE,MAP_SHARED,shmid,0);
	sscanf(v[1],"%d",&n);
	printf("[C] : Printing : \n");
	n = atoi(v[1]);
	n1=0,n2=1;
	sprintf(psm,"%d ",n1);
	psm+=strlen(psm);
	sprintf(psm,"%d ",n2);
	psm+=strlen(psm);
	printf("%d %d ",n1,n2);
	for(i=2;i<n;i++)
	{
		n3=n1+n2;
		sprintf(psm,"%d ",n3);
		psm+=strlen(psm);
		printf("%d ",n3);
		n1=n2;
		n2=n3;
	}
	printf("\n");
	sprintf(psm,"\n");
	shmctl(shmid,IPC_RMID,NULL);
}
