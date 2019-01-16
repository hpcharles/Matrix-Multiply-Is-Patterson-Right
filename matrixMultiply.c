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

	cleanMatrix	((void*)a, MATRIX_A);	cleanMatrix	((void*)b, MATRIX_B);
	randMatrix	((void*)a, MATRIX_A);	randMatrix	((void*)b, MATRIX_B);
	printMatrix ((void*)a, MATRIX_A);	printMatrix ((void*)b, MATRIX_B);

	time		= 0;
	ticktime	= getticks();

	for (i = 0; i< nbIteration; i++)
	{
		cleanMatrix((void*)c, MATRIX_RES);
		long long timeusec_local = start();
		mulMatrix(a, b, c);
		time += stop(timeusec_local);
	}
	ticktime = getticks() - ticktime;

	LOGGER (LOGGER_FLAG_TIME, "usec  & ticks time of %-5d iterations: %10lld %10lld\n", nbIteration,	time,				ticktime);
	LOGGER (LOGGER_FLAG_TIME, "usec  & ticks time of %-5d iteration : %10lld %10lld\n", 1,				time/nbIteration,	ticktime/nbIteration);
	printMatrix (c, MATRIX_RES);

	#ifdef CHECK_RESULT
		checkResult_matrixMult(a, b, c);
	#endif

	return 0;
}
