#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pthread.h>
#include "MatrixUtils.h"
tMatrix a, b;	/* Input matrices */
tMatrix c;		/* Result matrice */

#define NTHREAD 6

typedef struct
{
  int threadId;
  tMatrix a, b, res;
  int line, NLines, NColumns;
} tStructArg;

tStructArg arrayStructArg[NTHREAD];
pthread_t threadPointer[NTHREAD];

void mulMatrixKernel(tMatrix a, tMatrix b, tMatrix res, int line, int NLines, int NColumns)
{
  int col, k;

  for (col = 0; col < NLines; col++)
	{
	  res[line][col] = 0;
	  for (k = 0; k < NColumns; k++)
		{
		  res[line][col] += a[line][k] * b[k][col];
		}
	}
}

static void  * runner(void *pData)
{
  tStructArg *in = (tStructArg *) pData;
  //  printf ("Start thread %d\n", in->threadId);
  mulMatrixKernel (in->a, in->b, in->res, in->line, in->NLines, in->NColumns);
  //  printf ("End thread %d\n", in->threadId);
  return NULL;
}

#define copyParam(a, b, res, NLines, NColumns, threadN) {	\
	arrayStructArg[threadN].threadId = threadN;	 \
	arrayStructArg[threadN].a = a;				 \
	arrayStructArg[threadN].b = b;				 \
	arrayStructArg[threadN].res = res;			 \
	arrayStructArg[threadN].line = line;		 \
	arrayStructArg[threadN].NLines = NLines;	 \
	arrayStructArg[threadN].NColumns = NColumns; \
}

void mulMatrix(tMatrix a, tMatrix b, tMatrix res, int NLines, int NColumns)
{
  int line, threadN, ret;

  for (line = 0; line < NLines; line+= NTHREAD)
	{
	  for (threadN = 0; threadN < NTHREAD; threadN++)
		{
		  //  mulMatrixKernel (a, b, res, line, NLines, NColumns);
		  copyParam(a, b, res, NLines, NColumns, threadN);
		  ret = pthread_create(&threadPointer[threadN], NULL, &runner, (void *)&arrayStructArg[threadN]);
		  if (0 != ret)
			{
			  printf ("Thread creation error\n");
			  exit(-1);
			}
		}
	  for (threadN = 0; threadN < NTHREAD; threadN++)
		{
		  pthread_join(threadPointer[threadN], NULL);
		}
	}
}

int main(int argc, char * argv[])
{
  long nColumns, nLines, nThread, reference;
  long long startTime, endTime, nOps;
  float duration, flops, speedup;

  if (argc < 5)
	{
	  printf("Not enough arguments <nLines> <nColumns> <referenceTime> <#treadNumber>\n");
	  return 0;
	}
  nLines     = atoi(argv[1]);
  nColumns   = atoi(argv[2]);
  nThread    = atoi(argv[3]);
  reference  = atoi(argv[4]);

  a = createMatrix(nLines, nColumns);
  randMatrix   (a, nLines, nColumns);
  b = createMatrix(nColumns, nLines);
  randMatrix   (b, nColumns, nLines);
  c = createMatrix(nLines, nLines);
  startTime = getTime();
  mulMatrix(a, b, c, nLines, nColumns);
  endTime = getTime();
  duration = (endTime-startTime)/1000000.0;
  nOps = 2 * nLines * nLines * nColumns/ 1000000;
  flops = nOps / duration;
  speedup = flops/reference;
  printf ("Version    ; size       ; time (s) ; #Gops ; flops; speedup\n");
  printf ("%10s ; %05ldx%05ld ;%5.2f; %d; %5.2f;%5.2f\n", "C pthread", nLines, nColumns, duration, (int) nOps, flops, speedup);
  printf ("Thread N %ld Dummy result : %f̣\n", nThread, c[0][0]);
  return 0;
}
