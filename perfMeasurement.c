#include <perfMeasurement.h>








/* \brief Operating system level time measurement */

struct timeval time;

long long start()
{
	struct timezone tz;
	gettimeofday (&time, &tz);
	return time.tv_sec*1000000+time.tv_usec;
}

long long stop(long long timeusec)
{
	long long fin;
	struct timezone tz;
	gettimeofday (&time, &tz);
	fin = time.tv_sec*1000000+time.tv_usec;
	return fin-timeusec;
}

/* Performance counter level time measurement
   https://stackoverflow.com/questions/29189935/rdtsc-timing-for-a-measuring-a-function */
typedef unsigned long long ticks;
ticks getticks(void)
{
	unsigned a, d;
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((ticks)a) | (((ticks)d) << 32);
}
