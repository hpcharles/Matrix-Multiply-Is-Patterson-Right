CC					= gcc
CFLAGS				= -Wall -g -Werror -DDEBUG_LOGGER -DCHECK_RESULT
SIZE				= 100
NB_ITERATION		= 1000
DIM_PROPERTY		= -DNLINE=${SIZE} -DNCOL=${SIZE}
EXECUTION_PARAMETER	= --logger t --nbIteration ${NB_ITERATION}



all						:
						make int   SIZE=${SIZE} CFLAGS_OPT="-O0"
						make int   SIZE=${SIZE} CFLAGS_OPT="-O3"
						make float SIZE=${SIZE} CFLAGS_OPT="-O0"
						make float SIZE=${SIZE} CFLAGS_OPT="-O3"


int						:	clean perfMeasurement.o																\
							util.o_int																			\
							matrixMultiply.o_int_naive		matrix.o_int_naive		matrix_naive.o_int_naive	\
							matrixMultiply.o_int_SIMD		matrix.o_int_SIMD		matrix_SIMD.o_int_SIMD
						$(call compileAndExecutePython,int)
						$(call compileAndExecuteNaive,int)
						$(call compileAndExecuteSIMD,int)


float					:	clean perfMeasurement.o																	\
							util.o_float																			\
							matrixMultiply.o_float_naive	matrix.o_float_naive	matrix_naive.o_float_naive		\
							matrixMultiply.o_float_SIMD		matrix.o_float_SIMD		matrix_SIMD.o_float_SIMD
#						$(call compileAndExecutePython,float)
						$(call compileAndExecuteNaive,float)
#						$(call compileAndExecuteSIMD,float)


clean					:
						rm -f MatrixMultiply_int MatrixMultiply_float *.o*


#------------------------------------------
# Generic compilation
#------------------------------------------
%.o						: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY}												-g -c -o $@ $^

#------
%.o_int					: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int								-g -c -o $@ $^


%.o_float				: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float							-g -c -o $@ $^


#------
%.o_int_naive			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int		-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


%.o_int_SIMD			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int		-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


#------
%.o_float_naive			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


%.o_float_SIMD			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


#------------------------------------------
# Compile and execute all the tests
# The first parameter is the data type
#------------------------------------------
define compileAndExecutePython
			$(call writeExecHeader, python)
			time ./MatrixMultiply.py ${SIZE} ${1}
endef


define compileAndExecuteNaive
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o matrixMultiply_${1}_naive	matrixMultiply.o_${1}_naive	matrix.o_${1}_naive matrix_naive.o_${1}_naive	util.o_${1} perfMeasurement.o
			$(call writeExecHeader, "naive C")
			./matrixMultiply_${1}_naive ${EXECUTION_PARAMETER}
endef


define compileAndExecuteSIMD
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o matrixMultiply_${1}_SIMD	matrixMultiply.o_${1}_SIMD matrix.o_${1}_SIMD	matrix_SIMD.o_${1}_SIMD		util.o_${1} perfMeasurement.o
			$(call writeExecHeader, "SIMD")
			./MatrixMultiply_${1}_SIMD ${EXECUTION_PARAMETER}
endef


#------------------------------------------
# Auxiliary functions
#------------------------------------------
define writeExecHeader
	echo
	echo "----------------------------------"
	echo "Execution of "${1} " version"
	echo "----------------------------------"
endef
