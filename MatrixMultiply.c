#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef TYPEELTFLT
typedef float typeelt;
#else
typedef int typeelt;
#endif




typedef typeelt tMatrix[NLINE][NCOL];

/* Operating system level time measurement */
struct timeval utime;

long long start()
{
	struct timezone tz;
	gettimeofday (&utime, &tz);
	return utime.tv_sec*1000000+utime.tv_usec;
}

long long stop(long long timeusec)
{
	long long fin;
	struct timezone tz;
	gettimeofday (&utime, &tz);
	fin = utime.tv_sec*1000000+utime.tv_usec;
	return fin-timeusec;
}

/* Performance counter level time measurement 
   https://stackoverflow.com/questions/29189935/rdtsc-timing-for-a-measuring-a-function */

typedef unsigned long long ticks;
static __inline__ ticks getticks(void)
{
	unsigned a, d;
	a = d = 0;
#if 0
	asm ("rdtsc" : "=a" (a), "=d" (d));
#endif
	return ((ticks)a) | (((ticks)d) << 32);
}

#ifdef TYPEELTFLT
	char printfFormat[] = "%08f ";
#else
	char printfFormat[] = "%08d ";
#endif  
void printMatrix(tMatrix a)
{
	int line, col;
	for (line = 0; line < NLINE; line++)
	{
		for (col = 0; col < NCOL; col++)
			printf(printfFormat, a[line][col]);
		printf("\n");
	}
	printf("\n");
}

void cleanMatrix(tMatrix a)
{
	int line, col;
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			a[line][col] = 0;
}

void sumMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col;
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			res[line][col] = a[line][col] + b[line][col];
}

long long mulMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col, k;
	long long timeusec = start();
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
		{
			res[line][col] = 0;
			for (k = 0; k < NCOL; k++)
				res[line][col] += a[line][k] * b[k][col];
		}
	return stop(timeusec);
}

void diagMatrix(tMatrix a, typeelt value)
{
	int indice, line;
	indice = (NLINE < NCOL)?NLINE:NCOL;
	for (line = 0; line < indice; line++)
		a[line][line] = value;
}

void firstLineMatrix(tMatrix a, typeelt value)
{
	int col;
	for (col = 0; col < NCOL; col++)
		a[0][col] = value;
}

void firstColMatrix(tMatrix a, typeelt value)
{
	int line;
	for (line = 0; line < NCOL; line++)
		a[line][0] = value;
}

void randMatrix(tMatrix a)
{
	int line, col;
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			a[line][col] = (typeelt) (rand () % 1000);
}

int main(int argc, char * argv[])
{
	tMatrix a, b, c;
	long long time;
	ticks ticktime;
	int i;
	cleanMatrix(a);  cleanMatrix(b);   cleanMatrix(c);
	randMatrix(a);  randMatrix(b);
	time = 0;
	ticktime = getticks();
	for (i = 0; i< 1000; i++)
		time += mulMatrix(a, b, c);
	ticktime = getticks() - ticktime;
	printf ("usec  & ticks time of 1000 iteration : %10lld %10lld\n", time, ticktime);
	printf ("usec  & ticks time of 1 iteration : %10lld %10lld\n", time/1000, ticktime/1000);
#if 0
	printMatrix (c);
#endif
	return 0;
}
