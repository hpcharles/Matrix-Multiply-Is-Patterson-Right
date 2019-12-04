#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#if TYPEELT == 1             /* FLT */
typedef float typeelt;
char printfFormat[] = "%08f ";
#elif TYPEELT == 2             /* INT */
typedef int typeelt;
char printfFormat[] = "%08d ";
#elif TYPEELT == 3             /* DBL */
typedef double typeelt;
char printfFormat[] = "%08g ";
#elif TYPEELT == 4             /* SHT */
typedef short typeelt;
char printfFormat[] = "%08d ";
#endif


typedef typeelt tMatrix[NLINE][NCOL];

/* Operating system level time measurement */
struct timeval utime;

long long getTime()
{
	struct timezone tz;
	gettimeofday (&utime, &tz);
	return utime.tv_sec*1000000+utime.tv_usec;
}

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

#if GEMMVARIANT == 1
#define GEMM mulMatrix
#elif  GEMMVARIANT == 2
#define GEMM mulMatrixTiled
#elif GEMMVARIANT == 3
#define GEMM mulMatrixVectorized
#else
#define GEMM pleaseDefineMulMatrix
#endif

long long mulMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col, k;

	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
		{
			res[line][col] = 0;
			for (k = 0; k < NCOL; k++)
				res[line][col] += a[line][k] * b[k][col];
		}
	return res[line-1][col-1];
}


/* Define the tile size (TS) by the line with of the L1 cache */
#define TS (int)(64 / sizeof(typeelt))
long long mulMatrixTiled(tMatrix a, tMatrix b, tMatrix res) 
{
  int i0, j0, k0, i1, j1, k1;
  for (i0 = 0; i0 < NLINE; i0 += TS)
    {
      for (j0 = 0; j0 < NLINE; j0 += TS)
        {
          for (k0 = 0; k0 < NLINE; k0 += TS)
            { 
              int max_i0 = (TS*(i0 + 1)) > NLINE? NLINE: TS*(i0 + 1);
              int max_j0 = (TS*(j0 + 1)) > NLINE? NLINE: TS*(j0 + 1);
              int max_k0 = (TS*(k0 + 1)) > NLINE? NLINE: TS*(k0 + 1);
              for (i1 = i0*TS; i1 < max_i0; i1++)
                {
                  for (j1 = j0*TS; j1 < max_j0; j1++)
                    {
                      for(k1 = k0*TS; k1 < max_k0; k1++)
                        {
                          res[i1][j1] += a[i1][k1] * b[j1][k1];
						}
					}
				}
			}
		}
	}
  return res[i1-1][j1-1];
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
	long long startTime, endTime, nOps;
    float duration;
	int i;

	cleanMatrix(a);  cleanMatrix(b);   cleanMatrix(c);
	randMatrix(a);  randMatrix(b);
	startTime = getTime();	
    for (i = 0; i < 1000; i++)
      GEMM(a, b, c);
	endTime = getTime();	
    duration = (endTime-startTime)/1000000.0;
    nOps = 2 * NLINE * NLINE * NLINE;
	printf ("Time %10f\n", duration);
	printf ("Ops %10lld\n",  nOps);
    printf ("Flops %10.2f\n",  (float) nOps / duration);
#if 0
	printMatrix (c);
#endif
	return 0;
}
