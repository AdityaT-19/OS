#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void *pro(void *arg);
void *sum(void *arg);
int s=0,p=1;

void main(int c,char *v[])
{
	pthread_t T1,T2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&T1,&attr,sum,v[1]);
	pthread_create(&T2,&attr,pro,v[1]);
	pthread_join(T1,NULL);
	pthread_join(T2,NULL);
	printf("Inside main thread.\n");
	printf("Sum = %d\nProduct = %d\n",s,p);
}

void *sum(void *pram)
{
	int n=atoi(pram);
	printf("Inside sum thread.\n");
	for(int i=1;i<=n;i++)
		s+=i;
	printf("sum thread complete\n");
}

void *pro(void *pram)
{
	int n=atoi(pram);
	printf("Inside pro thread.\n");
	for(int i=2;i<=n;i++)
		p*=i;
	printf("pro thread complete\n");
}
