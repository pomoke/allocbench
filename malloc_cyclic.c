#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "mark.h"

#define MB (1024*1024)
//usage:malloc-cyclic [size:MB] [round]
int main(int argc,char **argv)
{
	if (argc!=2)
	{
		fprintf(stderr,"Usage:%s [size]\n",argv[0]);
		return 1;
	}
	int size,round=100,total,pagesize,unstd=0;
	pagesize=sysconf(_SC_PAGESIZE);
	sscanf(argv[1],"%d",&size);
	total=MB/pagesize*size;
	switch(size)
	{
		case 256:
			round=1000;
			break;
		case 512:
			round=500;
			break;
		case 1024:
			round=200;
			break;
		case 2048:
			round=200;
			break;
		default:
			round=200;
			unstd=1;
			puts("You are not using a standard size.Score unavailable.");
	}
	fprintf(stderr,"Allocate %d MB,%d pages,%d cycles,pagesize %d\n",size,total,round,pagesize);
	char **p=malloc(sizeof(char *)*total+1);
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
		for (int j=0;j<total;j++)
		{
			page=malloc(pagesize);
			if (page==NULL)
			{
				puts("Failed to allocate.");
				return 1;
			}
			*page='a';
			p[j]=page;
		}	
		//Free
		for (int j=0;j<total;j++)
		{
			free(p[j]);
		}
	}
	ret=clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&b);
	putc('\n',stderr);
	printf("Running time %lld\n",timediff(a,b));
	if (!unstd)
	{
		printf("Score %lld\n",score(timediff(a,b),size));
	}

	return 0;
}
