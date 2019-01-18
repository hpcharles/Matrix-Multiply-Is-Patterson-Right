/*
 * utilSIMD.h
 *
 *  Created on: 17 janv. 2019
 *      Author: rs254702
 */

#ifndef UTILSIMD_H_
#define UTILSIMD_H_


#include <pmmintrin.h>


/**
 * \returns the sum of the 4 floats contained within the input vector
 */
__inline__ float addElemSimdVect(__m128 vect);



#endif /* UTILSIMD_H_ */
