CC				= gcc
CFLAGS			= -Wall -g -Werror
SIZE			= 3
NB_ITERATION	= 1000
DIM_PROPERTY	= -DNLINE=${SIZE} -DNCOL=${SIZE}




all			:
			make int   SIZE=${SIZE} CFLAGS_OPT="-O0"
			make int   SIZE=${SIZE} CFLAGS_OPT="-O3"
			make float SIZE=${SIZE} CFLAGS_OPT="-O0"
			make float SIZE=${SIZE} CFLAGS_OPT="-O3"


int			: clean MatrixMultiply.o_int MatrixMultiplyNaive.o_int MatrixMultiplySIMD.o_int util.o_int perfMeasurement.o
			$(call compileAndExecuteAll,int)

float		: clean MatrixMultiply.o_float MatrixMultiplyNaive.o_float util.o_float perfMeasurement.o
			$(call compileAndExecuteAll,float)


clean		:
			rm -f MatrixMultiply_int MatrixMultiply_float *.o*


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
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o MatrixMultiply_${1} MatrixMultiply.o_${1} MatrixMultiplyNaive.o_${1} util.o_${1} perfMeasurement.o
			time ./MatrixMultiply_${1} --logger + --nbIteration ${NB_ITERATION}
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o MatrixMultiply_${1} MatrixMultiply.o_${1} MatrixMultiplySIMD.o_${1} util.o_${1} perfMeasurement.o
			time ./MatrixMultiply_${1} --logger + --nbIteration ${NB_ITERATION}
endef
