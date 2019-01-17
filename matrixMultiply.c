#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "util.h"
#include "perfMeasurement.h"










int main(int argc, char * argv[])
{
	char loggerFlag[128];
	unsigned int nbIteration;
	long long time;
	ticks ticktime;
	int i;
	tMatrix_a a;
	tMatrix_b b;
	tMatrix_res c;

	extractParameter(argc, argv, loggerFlag, &nbIteration);
	LOGGER_Init(loggerFlag);

	cleanMatrix	(&a, MATRIX_A);	cleanMatrix	(&b, MATRIX_B);
	randMatrix	(&a, MATRIX_A);	randMatrix	(&b, MATRIX_B);


/*
	b[0][0]	= 1;	b[1][0]	= 0;	b[2][0]	= 0;	b[3][0]	= 0;	b[4][0]	= 1;
	b[0][1]	= 0;	b[1][1]	= 1;	b[2][1]	= 0;	b[3][1]	= 0;	b[4][1]	= 1;
	b[0][2]	= 0;	b[1][2]	= 0;	b[2][2]	= 1;	b[3][2]	= 0;	b[4][2]	= 1;
	b[0][3]	= 0;	b[1][3]	= 0;	b[2][3]	= 0;	b[3][3]	= 1;	b[4][3]	= 1;
	b[0][4]	= 0;	b[1][4]	= 0;	b[2][4]	= 0;	b[3][4]	= 0;	b[4][4]	= 1;


	SET_MATRIX_GENERIC(b, 0, 0, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 0, 1, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 0, 2, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 0, 3, 0, MATRIX_B);
	SET_MATRIX_GENERIC(b, 1, 0, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 1, 1, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 1, 2, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 1, 3, 0, MATRIX_B);
	SET_MATRIX_GENERIC(b, 2, 0, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 2, 1, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 2, 2, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 2, 3, 0, MATRIX_B);
	SET_MATRIX_GENERIC(b, 3, 0, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 3, 1, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 3, 2, 0, MATRIX_B);	SET_MATRIX_GENERIC(b, 3, 3, 0, MATRIX_B);
*/



	time		= 0;
	ticktime	= getticks();

	for (i = 0; i< nbIteration; i++)
	{
		cleanMatrix(&c, MATRIX_RES);
		long long timeusec_local = start();
		mulMatrix(a, b, c);
		time += stop(timeusec_local);
	}
	ticktime = getticks() - ticktime;

	LOGGER (LOGGER_FLAG_TIME, "usec  & ticks time of %-5d iterations: %10lld %10lld\n", nbIteration,	time,				ticktime);
	LOGGER (LOGGER_FLAG_TIME, "usec  & ticks time of %-5d iteration : %10lld %10lld\n", 1,				time/nbIteration,	ticktime/nbIteration);

	#ifdef DEBUG_LOGGER
		printMatrix (&a,	MATRIX_A);
		printMatrix (&b,	MATRIX_B);
		printMatrix (&c,	MATRIX_RES);
	#endif
	#ifdef CHECK_RESULT
		checkResult_matrixMult(a, b, c);
	#endif

	return 0;
}
