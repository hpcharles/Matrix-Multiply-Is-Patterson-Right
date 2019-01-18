/*
 * utilSIMD.c
 *
 *  Created on: 17 janv. 2019
 *      Author: rs254702
 */

#include "utilSIMD.h"





__inline__ float addElemSimdVect(__m128 vect)
{
	__m128 res;

	res = _mm_hadd_ps(vect, vect);
	res = _mm_hadd_ps(res, res);

	return res[3];
}
