#include <stdio.h>
#include <stdlib.h>

#ifdef  __x86_64
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <emmintrin.h>
#endif

#include "MatrixUtils.h"

tMatrix a, b;	/* Input matrices */
tMatrix c;		/* Result matrice */

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

void mulMatrix(tMatrix a, tMatrix b, tMatrix res, int NLines, int NColumns)
{
  int line;

  for (line = 0; line < NLines; line++)
	{
	  mulMatrixKernel (a, b, res, line, NLines, NColumns);
	}
}

int main(int argc, char * argv[])
{
  long long startTime, endTime, nOps;
  float duration, flops, speedup;
  long nColumns, nLines;
  long reference;

  if (argc < 4)
	{
	  printf("Not enough arguments <nLines> <nColumns> <referenceTime>\n");
	  return 0;
	}
  nLines     = atoi(argv[1]);
  nColumns   = atoi(argv[2]);
  reference  = atoi(argv[3]);

  a = createMatrix(nLines, nColumns);
  b = createMatrix(nColumns, nLines);
  c = createMatrix(nLines, nLines);
  randMatrix(a, nLines, nColumns);
  randMatrix(b, nColumns, nLines);
#if PRINT
  printMatrix (a, nLines, nColumns);
  printMatrix (b, nColumns, nLines);
  printMatrix (c, nLines, nLines);
#endif
  startTime = getTime();
  mulMatrix(a, b, c, nLines, nColumns);
  endTime = getTime();
  duration = (endTime-startTime)/1000000.0;
  nOps = 2 * nLines * nLines * nColumns/1000000;
  flops = nOps / duration;
  speedup = flops/reference;
  printf ("Version    ; size       ; time (s) ; #Gops ; flops; speedup\n");
  printf ("%10s ; %05ldx%05ld ; %5.2f; %d  ; %5.2f; %5.2f\n", "C", nLines, nColumns, duration, (int) nOps, flops, speedup);
  printf ("Dummy result : %f̣\n", c[0][0]);
#if PRINT
  printMatrix (c);
#endif
  return 0;
}
