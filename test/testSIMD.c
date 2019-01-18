#include <pmmintrin.h>
#include <stdio.h>
#include <stdlib.h>


#define DATA_TYPE	int
//					4294967295
#define VAL			10
#define SIZE		8
#define SIZE_VECT	4


int main(int argc, char * argv[])
{
	DATA_TYPE tabA[SIZE], tabB[SIZE], tabRes[SIZE];
	DATA_TYPE *ptrA = tabA, *ptrB = tabB, *ptrRes = tabRes;

	__m128 vectA, vectB, vectRes;
	int k;

	for(k=0; k<SIZE; k++)
	{
		tabA[k]		= VAL		+ k;
		tabB[k]		= VAL*10	+ k;
		tabRes[k]	= -1;
	}

	for(k=0; k<SIZE; k+=SIZE_VECT)
	{
		vectA	= _mm_loadu_ps	((float*)ptrA);
		vectB	= _mm_loadu_ps	((float*)ptrB);
		vectRes	= _mm_add_ps	(vectA, vectB);

		_mm_storeu_ps((float*)ptrRes, vectRes);

		ptrA	+= SIZE_VECT;
		ptrB	+= SIZE_VECT;
		ptrRes	+= SIZE_VECT;
	}

	for(k=0; k<SIZE; k++)
	{
		printf("%3d: %10.1f    %10.1f    %10.1f : %s\n", k, (float)tabA[k], (float)tabB[k], (float)tabRes[k], (tabRes[k] == tabA[k] + tabB[k]) ? "TRUE" : "FALSE");
	}

	return 0;
}
