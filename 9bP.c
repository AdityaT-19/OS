#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>

void main(int c,char *v[])
{
	int n,i;
	pid_t id;
	void *psm;
	int shmid;
	shmid=shmget((key_t)1125,1024,0666|IPC_CREAT);
	psm = shmat(shmid,NULL,0666);
	sscanf(v[1],"%d",&n);
	id=fork();
	if(id == 0)
		execlp("./odd","odd",v[1],NULL);
	else
	{
		wait(NULL);
		printf("[P] : Child process complete\n");
		printf("[P] : Printing : \n");
		printf("%s\n", (char *)psm);
		shmdt(psm);
	}
}
