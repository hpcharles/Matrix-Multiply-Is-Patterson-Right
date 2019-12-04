#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <emmintrin.h>

#if TYPEELT == 1             /* FLT */
typedef float typeelt;
char printfFormat[] = "%010.2f ";
#elif TYPEELT == 2             /* INT */
typedef int typeelt;
char printfFormat[] = "%010d ";
#elif TYPEELT == 3             /* DBL */
typedef double typeelt;
char printfFormat[] = "%010.2g ";
#elif TYPEELT == 4             /* SHT */
typedef short typeelt;
char printfFormat[] = "%010d ";
#endif


typedef typeelt tMatrix[NELT][NELT];

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
	for (line = 0; line < NELT; line++)
	{
		for (col = 0; col < NELT; col++)
			printf(printfFormat, a[line][col]);
		printf("\n");
	}
	printf("\n");
}

void cleanMatrix(tMatrix a)
{
	int line, col;
	for (line = 0; line < NELT; line++)
		for (col = 0; col < NELT; col++)
			a[line][col] = 0;
}

void sumMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col;
	for (line = 0; line < NELT; line++)
		for (col = 0; col < NELT; col++)
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

/* Define vector operation */
#define VECTYPE __m256
#define vec_set(e7, e6, e5, e4, e3, e2, e1, e0) _mm256_set_ps(e7, e6, e5, e4, e3, e2, e1, e0)
#define vec_load(ptr)     _mm256_load_ps(ptr)
#define vec_setz()        _mm256_setzero_ps()
#define vec_add(v1, v2)   _mm256_add_ps(v1, v2)
#define vec_mul(v1, v2)   _mm256_mul_ps(v1, v2)
#define vec_hadd(v1, v2)  _mm256_hadd_ps(v1, v2)
#define vec_store(ptr, v) _mm256_store_ps(ptr, v)
#define vec_extract(v, x) _mm256_extract_ps(v, x)
#define vec_broadcast(x)  _mm256_set1_ps(x)

/* Define the tile size (TS) by the line with of the L1 cache */
#define TS (int)(64 / sizeof(typeelt))
float mulMatrixVectorized (tMatrix a, tMatrix b, tMatrix res) 
{  
  int i0, j0, k0; /* , i1, j1, k1;                              */

  for (i0 = 0; i0 < NELT; i0 += TS)
    {                                    
      for (j0 = 0; j0 < NELT; j0 += TS)
        {                                
          for (k0 = 0; k0 < NELT; k0 += TS)
            {                            
#if 0
              int max_i0 = (i0 + TS) > NELT? NELT: i0 + TS;                   
              int max_j0 = (j0 + TS) > NELT? NELT: j0 + TS;               
              int max_k0 = k0 + TS > NELT? NELT: k0 + TS;           
              VECTYPE va, vb, vres;   
              for (i1 = i0; i1 < max_i0; i1++)
                {                              
                  for (j1 = j0; j1 < max_j0; j1++)
                    {                          
                      c = vec_setz();                                         
                      for(k1 = k0; k1 < max_k0; k1 += ELPERVEC) 
                        {             
                          va = vec_load(&a[i1 * NELT + k1]);                      
                          vb = vec_load(&b[j1 * NELT + k1]);                      
                          vres = vec_add(res, vec_mul(a, b));                      
                        }                                                       
                      vres = vec_reduce_add(vres);                                  
                      res[i1 * TS + j1] = (float)vres[0];                  
                    }                                                           
                }                                                               
#endif
            }                                                                   
        }                                                                       
    }                                                                           
  return res[0][0];
}                                                                               


float mulMatrix(tMatrix a, tMatrix b, tMatrix res)
{
  int line, col, k;
  
  for (line = 0; line < NELT; line++)
    for (col = 0; col < NELT; col++)
      {
        res[line][col] = 0;
        for (k = 0; k < NELT; k++)
          {
             res[line][col] += a[line][k] * b[k][col];
          }
       }
   return res[line-1][col-1];
}

float mulMatrixTiled(tMatrix a, tMatrix b, tMatrix res) 
{
  int line0, col0, k0, line1, col1, k1;
  for (line0 = 0; line0 < NELT; line0 += TS)
    {
      for (col0 = 0; col0 < NELT; col0 += TS)
        {
          for (k0 = 0; k0 < NELT; k0 += TS)
            { 
              for (line1 = 0; line1 < TS; line1++)
                {
                  for (col1 = 0; col1 < TS; col1++)
                    {
                      for(k1 = 0; k1 < TS; k1++)
                        {
                          res[line0+line1][col0+col1] += a[line0+line1][k0+k1] * b[k0+k1][col0+col1];
						}
					}
				}
			}
		}
	}
  return res[0][0];
}

void randMatrix(tMatrix a)
{
	int line, col;
	for (line = 0; line < NELT; line++)
		for (col = 0; col < NELT; col++)
			a[line][col] = (typeelt) (rand () % 100);
}

int main(int argc, char * argv[])
{
	tMatrix a, b, c;
	long long startTime, endTime, nOps;
    float duration, result;
	int i;

	cleanMatrix(a);  cleanMatrix(b);   cleanMatrix(c);
	randMatrix(a);  randMatrix(b);
#if PRINT
	printMatrix (a);	
    printMatrix (b);
    printMatrix (c);
#endif
	startTime = getTime();	
    #define ITER 100
    for (i = 0; i < ITER; i++)
      result = GEMM(a, b, c);
	endTime = getTime();	
    duration = (endTime-startTime)/1000000.0;
    nOps = 2 * NELT * NELT * NELT;
	printf ("Result %10f\n", result);
	printf ("Time %10f\n", duration/ITER);
	printf ("Ops %10lld\n",  nOps);
    printf ("Flops %10.2f\n",  (float) nOps / (duration/ITER));
#if PRINT
	printMatrix (c);
#endif
	return 0;
}
