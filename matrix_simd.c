#include <xmmintrin.h>

#include "matrix.h"










void sumMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{

}


void mulMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{
	unsigned int line, col, k, k1;
	DATA_TYPE *b_addr, *res_addr;
	__m128 vectA, vectB, vectRes, vectMul;

	unsigned int vectorSIze_elem = VECTOR_SIZE / sizeof(DATA_TYPE);		// Number of elements in a vector
	unsigned int nbrBlockColumn = (int)(NCOL / vectorSIze_elem) * vectorSIze_elem;

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrixes(%d line, %d column) with SIMD vectors of size %d elements\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL, vectorSIze_elem);

	for (line = 0; line < NLINE; line++)
	{
		for (col = 0; col < NCOL; col++)
		{
			vectA	= _mm_set1_ps	((float)a[line][col]);
			b_addr	= b[col];
			res_addr= res[line];

			for (k=0; k<nbrBlockColumn; k+=vectorSIze_elem)				// Compute the matrix that fits within the vectors
			{
				vectB	= _mm_loadu_ps	((float*)b_addr);
				vectRes	= _mm_loadu_ps	((float*)res_addr);

				vectMul	= _mm_mul_ps	(vectA, vectB);
				vectRes	= _mm_add_ps	(vectRes, vectMul);

				_mm_storeu_ps((float*)res_addr, vectRes);

				b_addr		= b_addr	+ vectorSIze_elem;
				res_addr	= res_addr	+ vectorSIze_elem;
			}
			for (k1=nbrBlockColumn; k1<NCOL; k1++)						// Compute the remaining cells of the matrix
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

