#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MB (1024*1024)
//usage:malloc-cyclic [size:MB] [round]
int main(int argc,char **argv)
{
	if (argc!=3)
	{
		fprintf(stderr,"Usage:%s [size] [round]\n",argv[0]);
		return 1;
	}
	int size=256,round=50,total,pagesize;
	pagesize=sysconf(_SC_PAGESIZE);
	sscanf(argv[1],"%d",&size);
	sscanf(argv[2],"%d",&round);
	total=MB/pagesize*size;
	fprintf(stderr,"Allocate %d MB,%d pages,%d cycles,pagesize %d\n",size,total,round,pagesize);
	char **p=malloc(sizeof(char *)*total+1);
	char *page;
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
	putc('\n',stderr);
	return 0;
}
