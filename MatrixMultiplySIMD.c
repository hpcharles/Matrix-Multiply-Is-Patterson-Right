#include "MatrixMultiply.h"
#include <xmmintrin.h>





#define VECTOR_SIZE		16	// In bytes (TODO: change with the default Intel macros)

//#define DATA_TYPE	int



void sumMatrix(tMatrix a, tMatrix b, tMatrix res)
{

}


void mulMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col, k;
	DATA_TYPE *b_addr, *res_addr;
	__m128 vectA, vectB, vectRes, vectMul;

	unsigned int vectorSIze_elem	= VECTOR_SIZE / sizeof(DATA_TYPE);	// Number of elements in a vector

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrixes(%d line, %d column) with SIMD vectors of size %d elements\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL, vectorSIze_elem);

	for (line = 0; line < NLINE; line++)
	{
		LOGGER(LOGGER_FLAG_UTIL, "\tLine %d\n", line);
		for (col = 0; col < NCOL; col++)
		{
			LOGGER(LOGGER_FLAG_UTIL, "\t\tColumn %d\n", col);
			vectA	= _mm_set1_ps	(a[line][col]);
			b_addr	= b[col];
			res_addr= res[line];

uint32_t *val = (uint32_t*) &vectA;
LOGGER(LOGGER_FLAG_UTIL, "\t\t\tLoad a(%f): %"PRIu32" %"PRIu32" %"PRIu32" %"PRIu32"\n", a[line][col], val[0], val[1], val[2], val[3]);
//LOGGER(LOGGER_FLAG_UTIL, "\t\t\tLoad a: %" PRIu32 " %" PRIu32 " %" PRIu32 " %" PRIu32 " \n", val[0], val[1], val[2], val[3]);

			for (k=0; k<NCOL; k+=vectorSIze_elem)
			{
				LOGGER(LOGGER_FLAG_UTIL, "\t\t\tK %d\n", col);

				vectB	= _mm_load_ps	(b_addr);
val = (uint32_t*) &vectB;
LOGGER(LOGGER_FLAG_UTIL, "\t\t\tLoad b: %f %f %f %f\n", val[0], val[1], val[2], val[3]);

				vectRes	= _mm_load_ps	(res_addr);
				LOGGER(LOGGER_FLAG_UTIL, "\t\t\tLoad res\n");

				vectMul	= _mm_mul_ps	(vectA, vectB);
				vectRes	= _mm_add_ps	(vectRes, vectMul);

				_mm_store_ps(res_addr, vectRes);
val = (uint32_t*) &vectRes;
LOGGER(LOGGER_FLAG_UTIL, "\t\t\tStore res: %f %f %f %f\n", val[0], val[1], val[2], val[3]);

				b_addr		= b_addr	+ vectorSIze_elem;
				res_addr	= res_addr	+ vectorSIze_elem;
			}
		}
	}
}


void diagMatrix(tMatrix a, DATA_TYPE value)
{

}


void firstLineMatrix(tMatrix a, DATA_TYPE value)
{

}


void firstColMatrix(tMatrix a, DATA_TYPE value)
{

}

