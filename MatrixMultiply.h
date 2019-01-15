#include "util.h"




/**
 * \warning: these functions assume that the matrix has been set to zero prior
 */


void	sumMatrix		(tMatrix a, tMatrix b, tMatrix res);
void	mulMatrix		(tMatrix a, tMatrix b, tMatrix res);
void	diagMatrix		(tMatrix a, DATA_TYPE value);
void	firstLineMatrix	(tMatrix a, DATA_TYPE value);
void	firstColMatrix	(tMatrix a, DATA_TYPE value);
