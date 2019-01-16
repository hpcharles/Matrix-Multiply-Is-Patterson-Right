#include "matrix.h"





void sumMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{
	int line, col;
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			res[line][col] = a[line][col] + b[line][col];
}

void mulMatrix(tMatrix_a a, tMatrix_b b, tMatrix_res res)
{
	int line, col, k;

	LOGGER(LOGGER_FLAG_UTIL, "Multiply %s matrixes(%d line, %d column) with naive algo\n", MACROS_VALUE_STRING(DATA_TYPE), NLINE, NCOL);
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
		{
			res[line][col] = 0;
			for (k = 0; k < NCOL; k++)
				res[line][col] += a[line][k] * b[k][col];
		}
}

void diagMatrix(tMatrix_a a, DATA_TYPE value)
{
	int indice, line;
	indice = (NLINE < NCOL)?NLINE:NCOL;
	for (line = 0; line < indice; line++)
		a[line][line] = value;
}

void firstLineMatrix(tMatrix_a a, DATA_TYPE value)
{
	int col;
	for (col = 0; col < NCOL; col++)
		a[0][col] = value;
}

void firstColMatrix(tMatrix_a a, DATA_TYPE value)
{
	int line;
	for (line = 0; line < NCOL; line++)
		a[line][0] = value;
}