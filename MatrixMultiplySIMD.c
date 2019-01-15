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
	for (line = 0; line < NLINE; line++)
	{
		for (col = 0; col < NCOL; col++)
		{
			vectA	= _mm_set1_ps	(a[line][col]);
			b_addr	= b[col];
			res_addr= res[line];

			for (k=0; k<NCOL; k+=vectorSIze_elem)
			{
				vectB	= _mm_load_ps	(b_addr);
				vectRes	= _mm_load_ps	(res_addr);
				vectMul	= _mm_mul_ps	(vectA, vectB);
				vectRes	= _mm_add_ps	(vectRes, vectMul);

				_mm_store_ps(res_addr, vectRes);

				b_addr		= b_addr	+ VECTOR_SIZE;
				res_addr	= res_addr	+ VECTOR_SIZE;
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

