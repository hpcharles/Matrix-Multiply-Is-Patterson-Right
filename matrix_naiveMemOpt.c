#include "matrix.h"




/**
 * \brief The first and the res matrices are line-major.   The second matrix is column-major
 * \description Custom algorithm of matrix multiplication in order to fit the caches
 */





// TODO change all the indexe-incrementations according to the current pointer
// TODO change the initial values of each loops to fit the caches









void sumMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{

}


void mulMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{
	int l, c, c2, lk, ck, c2k;

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrices(%d line, %d column) with naive algo tunned to fit the caches\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL);

	size_t cacheLineSize= cacheL1_line_size_linux();						// In bytes
	size_t nbrCacheLine	= 	cacheL1_size_linux() / cacheLineSize	-		// Total number of caches lines to use
							(cacheL1_size_linux()*10 / cacheLineSize)/100;	//		Remove 10% of the cache lines to ensure that we still fit in it despite the concurrent workload
	size_t halfCacheLine = nbrCacheLine/2;

	for (c= 0; c<NCOL; c+=cacheLineSize)
	{
		for (l= 0; l<NLINE; l+=halfCacheLine)
		{
			for (c2= 0; c2<NCOL; c2+=halfCacheLine)
			{
				for (lk= 0; lk<halfCacheLine; lk++)
				{
					for (c2k= 0; c2k<halfCacheLine; c2k++)
					{
						for (ck= 0; ck<cacheLineSize; ck++)
						{
							res	[l+lk]	[c2+c2k]	+=
							a	[l+lk]	[c+ck]		*
							b	[c2+c2k][c+ck];
						}
					}
				}
			}
		}
	}
//printf("AAAAAAAAAAAAAAAAAAAA\n");
}


void diagMatrix(tMatrix_a a, DATA_TYPE value)
{

}


void firstLineMatrix(tMatrix_a a, DATA_TYPE value)
{

}


void firstColMatrix(tMatrix_a a, DATA_TYPE value)
{

}
