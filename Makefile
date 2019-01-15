CC				= gcc
CFLAGS			= -Wall -g -Werror -DDEBUG_LOGGER
SIZE			= 4
NB_ITERATION	= 1 #1000
DIM_PROPERTY	= -DNLINE=${SIZE} -DNCOL=${SIZE}




all			:
			make int   SIZE=${SIZE} CFLAGS_OPT="-O0"
			make int   SIZE=${SIZE} CFLAGS_OPT="-O3"
			make float SIZE=${SIZE} CFLAGS_OPT="-O0"
			make float SIZE=${SIZE} CFLAGS_OPT="-O3"


int			: clean MatrixMultiply.o_int	MatrixMultiplyNaive.o_int	MatrixMultiplySIMD.o_int	util.o_int		perfMeasurement.o
#			$(call compileAndExecutePython,int)
			$(call compileAndExecuteNaive,int)
#			$(call compileAndExecuteSIMD,int)

float		: clean MatrixMultiply.o_float	MatrixMultiplyNaive.o_float	MatrixMultiplySIMD.o_float	util.o_float	perfMeasurement.o
#			$(call compileAndExecutePython,float)
#			$(call compileAndExecuteNaive,float)
			$(call compileAndExecuteSIMD,float)


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
# The first parameter is the data type
#------------------------------------------
define compileAndExecutePython
#			time ./MatrixMultiply.py ${SIZE} ${1}
endef


define compileAndExecuteNaive
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o MatrixMultiply_${1} MatrixMultiply.o_${1} MatrixMultiplyNaive.o_${1} util.o_${1} perfMeasurement.o
			time ./MatrixMultiply_${1} --logger + --nbIteration ${NB_ITERATION}
endef


define compileAndExecuteSIMD
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o MatrixMultiply_${1} MatrixMultiply.o_${1} MatrixMultiplySIMD.o_${1} util.o_${1} perfMeasurement.o
			time ./MatrixMultiply_${1} --logger + --nbIteration ${NB_ITERATION}
endef
