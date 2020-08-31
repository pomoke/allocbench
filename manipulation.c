#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "mark.h"
#define COUNT 1000000
#define SEQ_COUNT 50000
//usage:manipulation [size:MB] [round]
int main(int argc,char **argv)
{
	if (argc!=1)
	{
		fprintf(stderr,"Usage:%s\n",argv[0]);
		return 1;
	}
	int size[]={13,15,0,60,128,0,47,1280,0,65537};
	int round=100,pagesize;
	pagesize=sysconf(_SC_PAGESIZE);
	size[2]=pagesize/2-1;
	size[5]=pagesize-3;
	size[8]=pagesize*2+13;
	char **p=malloc(sizeof(char *)*COUNT+1);
	if (p==NULL)
	{
		fprintf(stderr,"Failed to allocate memory.\n");
		return 1;
	}
	char *page;
	int ret;
	struct timespec a,b;
	ret=clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&a);
	if (ret)
	{
		perror("clock_gettime");
		return 1;
	}
	for(int i=0;i<round;i++)
	{
		//Allocate
		putc('.',stderr);
		//Small allocation
		for (int k=0;k<COUNT;k++)
		{
			page=malloc(16);
			if (page==NULL)
			{
				fprintf(stderr,"Failed to allocate memory\n");
				return 1;
			}
			else
				p[k]=page;
		}
		//Reversed free
		for (int k=COUNT-1;k>=0;k--)
			free(p[k]);
		
		//Sequenced Allocation
		for (int k=0;k<SEQ_COUNT;k++)
		{
			page=malloc(size[k%10]);
			if (page==NULL)
			{
				fprintf(stderr,"Failed to allocate memory.\n");
				return 1;
			}
			p[k]=page;
		}
		for (int k=0;k<SEQ_COUNT;k++)
			free(p[k]);
	}
	ret=clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&b);
	if (ret)
	{
		perror("clock_gettime");
		return 1;
	}
	putc('\n',stderr);
	printf("Time %lld,score %lld\n",timediff(a,b),score_m(timediff(a,b)));
	return 0;
}
