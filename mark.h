//#include <sys/time.h>
//return nanoseconds

//Referrence time
#define M2048 175437774327l
#define M1024 88126506319l
#define M512 110723744077l
#define M256 110672218163l
#define TIME_MANI 7604680978l
#define SCORE(t,r) ((r)*10000l/(t))
long long timediff(struct timespec begin,struct timespec end)
{
	return (end.tv_sec-begin.tv_sec)*1000000000+end.tv_nsec-begin.tv_nsec;
}

long long score(long long rt,int size)
{
	switch(size)
	{
		case 2048:
			return SCORE(rt,M2048);
			break;
		case 1024:
			return SCORE(rt,M1024);
			break;
		case 512:
			return SCORE(rt,M512);
			break;
		case 256:
			return SCORE(rt,M256);
			break;
		default:
			return -1;
			break;
	}
}

long long score_m(long long rt)
{
	return SCORE(rt,TIME_MANI);
}
