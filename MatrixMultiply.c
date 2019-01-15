#include "MatrixMultiply.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "perfMeasurement.h"









int main(int argc, char * argv[])
{
	char loggerFlag[128];
	unsigned int nbIteration;
	tMatrix a, b, c;
	long long time;
	ticks ticktime;
	int i;

	extractParameter(argc, argv, loggerFlag, &nbIteration);
	LOGGER_Init(loggerFlag);

	cleanMatrix(a);  cleanMatrix(b);   cleanMatrix(c);
	randMatrix(a);  randMatrix(b);

	time = 0;
	ticktime = getticks();
	for (i = 0; i< nbIteration; i++)
	{
		long long timeusec_local = start();
		mulMatrix(a, b, c);
		time += stop(timeusec_local);
	}
	ticktime = getticks() - ticktime;

	LOGGER (LOGGER_FLAG_MAIN, "usec  & ticks time of %-5d iterations: %10lld %10lld\n", nbIteration,	time,				ticktime);
	LOGGER (LOGGER_FLAG_MAIN, "usec  & ticks time of %-5d iteration : %10lld %10lld\n", 1,				time/nbIteration,	ticktime/nbIteration);
	printMatrix (c);

//printf("\n\n\n\nsize(%s) = %d\n", MACROS_VALUE_STRING(DATA_TYPE), sizeof(DATA_TYPE));
	return 0;
}
