#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "util.h"
#include "perfMeasurement.h"










int main(int argc, char * argv[])
{
	char loggerFlag[128];
	int nbIteration, i;
	long long time;
	ticks ticktime;
	tMatrix_a a;
	tMatrix_b b;
	tMatrix_res c;

	extractParameter(argc, argv, loggerFlag, &nbIteration);
	LOGGER_Init(loggerFlag);

	cleanMatrix	(&a, MATRIX_A);	cleanMatrix	(&b, MATRIX_B);
	randMatrix	(&a, MATRIX_A);	randMatrix	(&b, MATRIX_B);

	time		= 0;
	ticktime	= getticks();

	for (i = 0; i< nbIteration; i+=1)
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
