#include "MatrixMultiply.h"





void sumMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col;
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
			res[line][col] = a[line][col] + b[line][col];
}

long long mulMatrix(tMatrix a, tMatrix b, tMatrix res)
{
	int line, col, k;
	long long timeusec = start();
	for (line = 0; line < NLINE; line++)
		for (col = 0; col < NCOL; col++)
		{
			res[line][col] = 0;
			for (k = 0; k < NCOL; k++)
				res[line][col] += a[line][k] * b[k][col];
		}
	return stop(timeusec);
}

void diagMatrix(tMatrix a, DATA_TYPE value)
{
	int indice, line;
	indice = (NLINE < NCOL)?NLINE:NCOL;
	for (line = 0; line < indice; line++)
		a[line][line] = value;
}

void firstLineMatrix(tMatrix a, DATA_TYPE value)
{
	int col;
	for (col = 0; col < NCOL; col++)
		a[0][col] = value;
}

void firstColMatrix(tMatrix a, DATA_TYPE value)
{
	int line;
	for (line = 0; line < NCOL; line++)
		a[line][0] = value;
}
