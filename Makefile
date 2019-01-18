CC					= gcc
CFLAGS				= -Wall -g -Werror -DDEBUG_LOGGER -DCHECK_RESULT -msse3 # The -mse3 option is used to solve compilation issues with function _mm_hadd_ps
CFLAGS_OPT			= -o0
#SIZE				= 48		Fails for SIMD int
#SIZE				= 50		Fails for SIMDInvertedB float
SIZE				= 4
NB_ITERATION		= 1
DIM_PROPERTY		= -DNLINE=${SIZE} -DNCOL=${SIZE}
EXECUTION_PARAMETER	= --nbIteration ${NB_ITERATION} --logger t#p

EXEC				=	matrixMultiply_float_naive				\
						matrixMultiply_float_simd				\
						matrixMultiply_float_simdInvertedB		\
						matrixMultiply_float_naiveMemOpt		\
						matrixMultiply_int_naive				\
						matrixMultiply_int_simd					\
						matrixMultiply_int_simdInvertedB		\
						matrixMultiply_int_naiveMemOpt




all						:
						make int   SIZE=${SIZE} CFLAGS_OPT="-O0"
						make int   SIZE=${SIZE} CFLAGS_OPT="-O3"
						make float SIZE=${SIZE} CFLAGS_OPT="-O0"
						make float SIZE=${SIZE} CFLAGS_OPT="-O3"


int						:	clean 																										\
							perfMeasurement.o utilSIMD.o																				\
							util.o_int																									\
							matrixMultiply.o_int_naive			matrix.o_int_naive			matrix_naive.o_int_naive					\
							matrixMultiply.o_int_simd			matrix.o_int_simd			matrix_simd.o_int_simd						\
							matrixMultiply.o_int_simdInvertedB	matrix.o_int_simdInvertedB	matrix_simdInvertedB.o_int_simdInvertedB	\
							matrixMultiply.o_int_naiveMemOpt	matrix.o_int_naiveMemOpt	matrix_naiveMemOpt.o_int_naiveMemOpt
#						$(call compileAndExecutePython,int)
#						$(call compileAndExecuteNaive,int)
#						$(call compileAndExecuteSimd,int)
#						$(call compileAndExecuteSimdInvertedB,int)
						$(call compileAndExecuteNaiveMemOpt,int)


float					:	clean																												\
							perfMeasurement.o utilSIMD.o																						\
							util.o_float																										\
							matrixMultiply.o_float_naive			matrix.o_float_naive			matrix_naive.o_float_naive					\
							matrixMultiply.o_float_simd				matrix.o_float_simd				matrix_simd.o_float_simd					\
							matrixMultiply.o_float_simdInvertedB	matrix.o_float_simdInvertedB	matrix_simdInvertedB.o_float_simdInvertedB	\
							matrixMultiply.o_float_naiveMemOpt		matrix.o_float_naiveMemOpt		matrix_naiveMemOpt.o_float_naiveMemOpt
#						$(call compileAndExecutePython,float)
#						$(call compileAndExecuteNaive,float)
#						$(call compileAndExecuteSimd,float)
#						$(call compileAndExecuteSimdInvertedB,float)
						$(call compileAndExecuteNaiveMemOpt,float)


clean					:
						rm -f *.o
						rm -f *.o_*


mrproper				: clean
						rm -rf ${EXEC}


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


%.o_int_simd			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int		-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


%.o_int_simdInvertedB	: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int		-DMATRIX_INVERTED_STATIC -g -c -o $@ $^


%.o_int_naiveMemOpt		: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=int		-DMATRIX_INVERTED_STATIC -g -c -o $@ $^


#------
%.o_float_naive			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


%.o_float_simd			: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-DMATRIX_SIMPLE_STATIC	-g -c -o $@ $^


%.o_float_simdInvertedB	: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-DMATRIX_INVERTED_STATIC -g -c -o $@ $^


%.o_float_naiveMemOpt	: %.c
						${CC} ${CFLAGS} ${DIM_PROPERTY} -DDATA_TYPE=float	-DMATRIX_INVERTED_STATIC -g -c -o $@ $^


#------------------------------------------
# Compile and execute all the tests
# The first parameter is the data type
#------------------------------------------
define compileAndExecutePython
			$(call writeExecHeader, ${1}, python)
			time ./MatrixMultiply.py ${SIZE} ${1}
endef


define compileAndExecuteNaive
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o matrixMultiply_${1}_naive	matrixMultiply.o_${1}_naive	matrix.o_${1}_naive matrix_naive.o_${1}_naive	util.o_${1} perfMeasurement.o
			$(call writeExecHeader, ${1}, "naive C")
			./matrixMultiply_${1}_naive ${EXECUTION_PARAMETER}
endef


define compileAndExecuteSimd
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o	matrixMultiply_${1}_simd		\
																matrixMultiply.o_${1}_simd		\
																matrix.o_${1}_simd				\
																matrix_simd.o_${1}_simd			\
																util.o_${1}						\
																perfMeasurement.o
			$(call writeExecHeader, ${1}, "SIMD")
			./matrixMultiply_${1}_simd ${EXECUTION_PARAMETER}
endef


define compileAndExecuteSimdInvertedB
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o	matrixMultiply_${1}_simdInvertedB				\
																matrixMultiply.o_${1}_simdInvertedB				\
																matrix.o_${1}_simdInvertedB						\
																matrix_simdInvertedB.o_${1}_simdInvertedB		\
																util.o_${1}										\
																perfMeasurement.o								\
																utilSIMD.o
			$(call writeExecHeader, ${1}, "SIMD with inverted 2nd matrix")
			./matrixMultiply_${1}_simdInvertedB ${EXECUTION_PARAMETER}
endef


define compileAndExecuteNaiveMemOpt
			${CC} ${CFLAGS}	${CFLAGS_OPT} ${DIM_PROPERTY} -o	matrixMultiply_${1}_naiveMemOpt				\
																matrixMultiply.o_${1}_naiveMemOpt			\
																matrix.o_${1}_naiveMemOpt					\
																matrix_naiveMemOpt.o_${1}_naiveMemOpt		\
																util.o_${1}									\
																perfMeasurement.o
			$(call writeExecHeader, ${1}, "naive C with inverted 2nd matrix and block split to fit caches")
			./matrixMultiply_${1}_naiveMemOpt ${EXECUTION_PARAMETER}
endef


#------------------------------------------
# Auxiliary functions
#------------------------------------------
define writeExecHeader
	echo
	echo "----------------------------------"
	echo "Execution of "${2} " version:"
	echo "    - Data type             :"${1}
	echo "    - Matrix size           : NLINE="${SIZE}" NCOL="${SIZE}
	echo "    - Compiler optimization : "${CFLAGS_OPT}
	echo "----------------------------------"
endef
