#include <xmmintrin.h>

#include "matrix.h"
#include "utilSIMD.h"



// TODO test: the following function does the same without inverting the matrix
// __m128 _mm_setr_ps (float e3, float e2, float e1, float e0)


/**
 * \brief The first and the res matrices are line-major.   The second matrix is column-major
 */

void sumMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{

}

void mulMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{
	unsigned int line, col, k;
	DATA_TYPE *a_addr, *b_addr;
	__m128 vectA, vectB, vectRes, vectMul;
//	__m128i vectA, vectB, vectRes, vectMul;

	unsigned int vectorSIze_elem = VECTOR_SIZE / sizeof(DATA_TYPE);		// Number of elements in a vector
	unsigned int nbrBlockColumn = (int)(NCOL / vectorSIze_elem) * vectorSIze_elem;

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrices(%d line, %d column) with SIMD vectors of size %d elements (inverted 2nd matrix)\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL, vectorSIze_elem);

	for (line = 0; line < NLINE; line++)
	{
		for (col = 0; col < NCOL; col++)
		{
			a_addr	= a[line];
			b_addr	= b[col];
			vectRes	= _mm_setzero_ps();
			for (k=0; k<nbrBlockColumn; k+=vectorSIze_elem)					// Compute the matrix that fits within the vectors
			{
				vectA	= _mm_loadu_ps	((float*)a_addr);
				vectB	= _mm_loadu_ps	((float*)b_addr);

				vectMul	= _mm_mul_ps	(vectA, vectB);
				vectRes	= _mm_add_ps	(vectRes, vectMul);

				a_addr		= a_addr	+ vectorSIze_elem;
				b_addr		= b_addr	+ vectorSIze_elem;
			}
			res[line][col] = addElemSimdVect(vectRes);

			for (k=nbrBlockColumn; k<NCOL; k++)								// Compute the remaining cells of the matrix
			{
				res[line][col] += a[line][k] * b[col][k];
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
