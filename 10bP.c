#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/wait.h>

void main(int c,char *v[])
{
	int n,n1,n2,n3,i;
	pid_t id;
	void *psm;
	int shmid;
	sscanf(v[1],"%d",&n);
	id=fork();
	if(id == 0)
		execlp("./prime","prime",v[1],v[2],NULL);
	else
	{
		wait(NULL);
		shmid=shm_open("A_OS",O_RDONLY,0666);
		ftruncate(shmid,1024);
		psm = mmap(0,1024,PROT_READ,MAP_SHARED,shmid,0);
		printf("[P] : Child process complete\n");
		printf("[P] : Printing : \n");
		printf("%s\n", (char *)psm);
		shm_unlink("A_OS");
	}
}