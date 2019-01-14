CC				= gcc
SIZE			= 3
NB_ITERATION	= 1000
DIM_PROPERTY	= -DNLINE=${SIZE} -DNCOL=${SIZE}



all			:
			make int   SIZE=${SIZE} CFLAGS="-O0 -Wall"
			make int   SIZE=${SIZE} CFLAGS="-O3 -Wall"
			make float SIZE=${SIZE} CFLAGS="-O0 -Wall"
			make float SIZE=${SIZE} CFLAGS="-O3 -Wall"


int			: MatrixMultiply.o_int MatrixMultiplyNaive.o_int util.o_int perfMeasurement.o
			$(call compileAndExecuteAll,int)

float		: MatrixMultiply.o_float MatrixMultiplyNaive.o_float util.o_float perfMeasurement.o
			$(call compileAndExecuteAll,float)


clean		:
			rm MatrixMultiply_int MatrixMultiply_float *.o*


#------------------------------------------
# Generic compilation
#------------------------------------------
%.o			: %.c
			${CC} ${CFLAGS} ${DIM_PROPERTY}						-g -c -o $@ $^


%.o_int		: %.c
			${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int		-g -c -o $@ $^


%.o_float	: %.c
			${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-g -c -o $@ $^


#------------------------------------------
# Compile and execute all the tests
#------------------------------------------
# The first parameter is the data type
define compileAndExecuteAll
			time ./MatrixMultiply.py ${SIZE} ${1}
			${CC} ${CFLAGS}	${DIM_PROPERTY} -o MatrixMultiply_${1} MatrixMultiply.o_${1} MatrixMultiplyNaive.o_${1} util.o_${1} perfMeasurement.o
			time ./MatrixMultiply_${1} --logger + --nbIteration ${NB_ITERATION}
endef