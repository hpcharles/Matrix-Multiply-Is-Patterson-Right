#include "matrix.h"










void checkResult_matrixMult(tMatrix_a a, tMatrix_b b, tMatrix_res result)
{
	int line, col, k;

	for (line = 0; line < NLINE; line++)
	{
		for (col = 0; col < NCOL; col++)
		{
			DATA_TYPE tmp = 0;
			for (k = 0; k < NCOL; k++)
			{
				tmp += GET_MATRIX_A(a, line, k) * GET_MATRIX_B(b, k, col);
			}
			if (tmp != GET_MATRIX_RES(result, line, col))
			{
				LOGGER_error(1, "Wrong result at line %d and column %d\n", line, col);
			}
		}
	}
}


void printMatrix(void *M, int TYPE)
{
	int line, col;
	char buffer[NCOL * 50], *bufferTmp;

	LOGGER(LOGGER_FLAG_RESULT, "Print the matrix %p of size: %d line and %d column\n", (DATA_TYPE**)M, NLINE, NCOL);
	for (line = 0; line < NLINE; line++)
	{
		bufferTmp = buffer;
		for (col = 0; col < NCOL; col++)
		{
			bufferTmp += sprintf(bufferTmp, PRINT_FORMAT, GET_MATRIX_GENERIC(M, line, col, TYPE));
		}
		LOGGER(LOGGER_FLAG_RESULT, "%s\n", buffer);
	}
	LOGGER(LOGGER_FLAG_RESULT, "\n");
}


void cleanMatrix(void *M, int TYPE)
{
	int line, col;

	LOGGER(LOGGER_FLAG_UTIL, "Clean the matrix %p of size: %d line and %d column\n", (DATA_TYPE**)M, NLINE, NCOL);
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			SET_MATRIX_GENERIC(M, line, col, 0, TYPE);
}


void randMatrix(void *M, int TYPE)
{
	int line, col;

	LOGGER(LOGGER_FLAG_UTIL, "Random-fill the matrix %p of size: %d line and %d column\n", (DATA_TYPE**)M, NLINE, NCOL);
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			SET_MATRIX_GENERIC(M, line, col, (DATA_TYPE) (rand () % 1000), TYPE);
}
