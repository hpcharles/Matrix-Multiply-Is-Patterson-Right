#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "MatrixUtils.h"

#if TYPEELT == 1               /* FLT */
char printfFormat[] = "%010.2f ";
#elif TYPEELT == 2             /* INT */
char printfFormat[] = "%010d ";
#elif TYPEELT == 3             /* DBL */
char printfFormat[] = "%010.2g ";
#elif TYPEELT == 4             /* SHT */
char printfFormat[] = "%010d ";
#endif

void printMatrix(tMatrix a, int nLines, int nColumns)
{
	int line, col;
	for (line = 0; line < nLines; line++)
	{
		for (col = 0; col < nColumns; col++)
			printf(printfFormat, a[line][col]);
		printf("\n");
	}
	printf("\n");
}

long long getTime()
{
  struct timeval utime; /* Operating system level time measurement */
  struct timezone tz;
  gettimeofday (&utime, &tz);
  return utime.tv_sec*1000000+utime.tv_usec;
}


tMatrix createMatrix(int NLines, int NCols)
{
	int line, col;
	tMatrix a;
	a = (tMatrix)malloc (NLines*sizeof (typeelt *));
	for (line = 0; line < NLines; line++)
	  {
		a[line] = (typeelt *)malloc (NCols*sizeof (typeelt));
		for (col = 0; col < NCols; col++)
		  {
			a[line][col] = 0;
		  }
	  }
	return a;
}

void randMatrix(tMatrix a, int NLines, int NCols)
{
	int line, col;
	for (line = 0; line < NLines; line++)
		for (col = 0; col < NCols; col++)
			a[line][col] = (typeelt) (rand () % 100);
}
