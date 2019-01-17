#ifndef MATRIX_MULTIPLY_H
#define MATRIX_MULTIPLY_H


#include "util.h"



#define MATRIX_A		0
#define MATRIX_B		1
#define MATRIX_RES		2


//#define MATRIX_SIMPLE_STATIC
//#define MATRIX_INVERTED_STATIC
//#define DATA_TYPE	float
//#define NLINE		10
//#define NCOL		10
/**
 * \brief Matrix definition
 */
#ifdef MATRIX_SIMPLE_STATIC
	typedef DATA_TYPE tMatrix_a										[NLINE]	[NCOL];
	typedef DATA_TYPE tMatrix_b										[NLINE]	[NCOL];
	typedef DATA_TYPE tMatrix_res									[NLINE]	[NCOL];

	#define	GET_MATRIX_A(			A,		line, col)			A	[line]	[col]
	#define	GET_MATRIX_B(			B,		line, col)			B	[line]	[col]
	#define	GET_MATRIX_RES(			RES,	line, col)			RES	[line]	[col]

	#define	SET_MATRIX_A(			A,		line, col, val)		A	[line]	[col]	= val
	#define	SET_MATRIX_B(			B,		line, col, val)		B	[line]	[col]	= val
	#define	SET_MATRIX_RES(			RES,	line, col, val)		RES	[line]	[col]	= val

#else
#ifdef MATRIX_INVERTED_STATIC
	typedef DATA_TYPE tMatrix_a										[NLINE]	[NCOL];
	typedef DATA_TYPE tMatrix_b										[NCOL]	[NLINE];
	typedef DATA_TYPE tMatrix_res									[NLINE]	[NCOL];

	#define	GET_MATRIX_A(			A,		line, col)			A	[line]	[col]
	#define	GET_MATRIX_B(			B,		line, col)			B	[col]	[line]
	#define	GET_MATRIX_RES(			RES,	line, col)			RES	[line]	[col]

	#define	SET_MATRIX_A(			A,		line, col, val)		A	[line]	[col]	= val
	#define	SET_MATRIX_B(			B,		line, col, val)		B	[col]	[line]	= val
	#define	SET_MATRIX_RES(			RES,	line, col, val)		RES	[line]	[col]	= val
#endif
#endif

//#define GET_MATRIX_GENERIC(M,line,col,TYPE)			(*((tMatrix_a*)M))[line][col]
//#define SET_MATRIX_GENERIC(M,line,col,val,TYPE)		(*((tMatrix_a*)M))[line][col] = val

#define GET_MATRIX_GENERIC(M,line,col,TYPE)		(TYPE == MATRIX_A) ? GET_MATRIX_A((*(tMatrix_a*)M), line, col)		: ( (TYPE == MATRIX_B) ? GET_MATRIX_B((*(tMatrix_b*)M), line, col)		: ( (TYPE == MATRIX_RES) ? GET_MATRIX_RES((*(tMatrix_res*)M), line, col)		: (DATA_TYPE)*LOGGER_error(1, "Unknown matrix type %d (GET_MATRIX_GENERIC)", TYPE) ) )
#define SET_MATRIX_GENERIC(M,line,col,val,TYPE)	(TYPE == MATRIX_A) ? SET_MATRIX_A((*(tMatrix_a*)M), line, col, val)	: ( (TYPE == MATRIX_B) ? SET_MATRIX_B((*(tMatrix_b*)M), line, col, val)	: ( (TYPE == MATRIX_RES) ? SET_MATRIX_RES((*(tMatrix_res*)M), line, col, val)	: (void)LOGGER_error(1, "Unknown matrix type %d (SET_MATRIX_GENERIC)", TYPE) ) )


/**
 * \warning: these functions assume that the matrix has been set to zero prior
 */
void	sumMatrix		(tMatrix_a a, tMatrix_b b, tMatrix_res res);
void	mulMatrix		(tMatrix_a a, tMatrix_b b, tMatrix_res res);
void	diagMatrix		(tMatrix_a a, DATA_TYPE value);
void	firstLineMatrix	(tMatrix_a a, DATA_TYPE value);
void	firstColMatrix	(tMatrix_a a, DATA_TYPE value);


/**
 * \brief Common matrix-management functions that are used by different modules
 * \parameter M: pointer on the input matrix.   Must be casted to one of the types: tMatrix_a, tMatrix_b, tMatrix_res
 * \parameter TYPE: macros corresponding to the matrix type.  Must be one of the macros: MATRIX_A, MATRIX_B, MATRIX_RES
 */
void checkResult_matrixMult(tMatrix_a a, tMatrix_b b, tMatrix_res result);
void printMatrix	(void *M, int TYPE);
void cleanMatrix	(void *M, int TYPE);
void randMatrix		(void *M, int TYPE);



#endif
