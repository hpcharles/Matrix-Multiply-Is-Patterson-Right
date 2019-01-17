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

	unsigned int vectorSIze_elem = VECTOR_SIZE / sizeof(DATA_TYPE);		// Number of elements in a vector
	unsigned int nbrBlockColumn = (int)(NCOL / vectorSIze_elem) * vectorSIze_elem;

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrixes(%d line, %d column) with SIMD vectors of size %d elements\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL, vectorSIze_elem);

	for (line = 0; line < NLINE; line++)
	{
		printf("Line = %d\n", line);
		for (col = 0; col < NCOL; col++)
		{
			printf("\tCol = %d\n", col);
			a_addr	= a[line];
			b_addr	= b[col];
			vectRes	= _mm_setzero_ps();
			for (k=0; k<nbrBlockColumn; k+=vectorSIze_elem)					// Compute the matrix that fits within the vectors
			{
				printf("\t\tk = %d\n", k);
				vectA	= _mm_loadu_ps	((float*)a_addr);
				vectB	= _mm_loadu_ps	((float*)b_addr);

				printf("A   = %5.0f, %5.0f, %5.0f, %5.0f\n", vectA[0], vectA[1], vectA[2], vectA[3]);
				printf("B   = %5.0f, %5.0f, %5.0f, %5.0f\n", vectB[0], vectB[1], vectB[2], vectB[3]);

				vectMul	= _mm_mul_ps	(vectA, vectB);
				vectRes	= _mm_add_ps	(vectRes, vectMul);

				printf("MUL = %5.0f, %5.0f, %5.0f, %5.0f\n", vectMul[0], vectMul[1], vectMul[2], vectMul[3]);
				printf("RES = %5.0f, %5.0f, %5.0f, %5.0f\n", vectRes[0], vectRes[1], vectRes[2], vectRes[3]);

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









/*

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
*/
void diagMatrix(tMatrix_a a, DATA_TYPE value)
{

}

void firstLineMatrix(tMatrix_a a, DATA_TYPE value)
{

}

void firstColMatrix(tMatrix_a a, DATA_TYPE value)
{

}
