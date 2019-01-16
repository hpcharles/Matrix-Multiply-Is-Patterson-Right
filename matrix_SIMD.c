#include <xmmintrin.h>

#include "matrix.h"





#define VECTOR_SIZE		16	// In bytes (TODO: change with the default Intel macros)

//#define DATA_TYPE	int



void sumMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{

}


void mulMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{
	int line, col, k, k1;
	DATA_TYPE *b_addr, *res_addr;
	__m128 vectA, vectB, vectRes, vectMul;

	unsigned int vectorSIze_elem = VECTOR_SIZE / sizeof(DATA_TYPE);		// Number of elements in a vector

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrixes(%d line, %d column) with SIMD vectors of size %d elements\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL, vectorSIze_elem);

	for (line = 0; line < NLINE; line++)
	{
		for (col = 0; col < NCOL; col++)
		{
			vectA	= _mm_set1_ps	(a[line][col]);
			b_addr	= b[col];
			res_addr= res[line];

			for (k=0; k<(NCOL-(vectorSIze_elem%NCOL)); k+=vectorSIze_elem)
			{
				vectB	= _mm_loadu_ps	(b_addr);
				vectRes	= _mm_loadu_ps	(res_addr);

				vectMul	= _mm_mul_ps	(vectA, vectB);
				vectRes	= _mm_add_ps	(vectRes, vectMul);

				_mm_storeu_ps(res_addr, vectRes);

				b_addr		= b_addr	+ vectorSIze_elem;
				res_addr	= res_addr	+ vectorSIze_elem;
			}
			for (k1=k; k1<NCOL; k1++)									// Compute the remaining cells
			{
				res[line][k1] += a[line][col] * b[col][k1];
			}
		}
	}
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

