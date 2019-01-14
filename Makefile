CC				= gcc
SIZE			= 20
NB_ITERATION	= 1000

all: 
	make int   SIZE=${SIZE} CFLAGS="-O0 -Wall"
	make int   SIZE=${SIZE} CFLAGS="-O3 -Wall"
	make float SIZE=${SIZE} CFLAGS="-O0 -Wall"
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall"


int:
	time ./MatrixMultiply.py ${SIZE} int
	${CC} ${CFLAGS} -g -DNLINE=${SIZE} -DNCOL=${SIZE} -DNB_ITERATION=${NB_ITERATION}				-o MatrixMultiply MatrixMultiply.c 
	time ./MatrixMultiply
float:
	time ./MatrixMultiply.py ${SIZE} float
	${CC} ${CFLAGS} -g -DNLINE=${SIZE} -DNCOL=${SIZE} -DNB_ITERATION=${NB_ITERATION} -DTYPEELTFLT	-o MatrixMultiply MatrixMultiply.c
	time ./MatrixMultiply
clean:
	rm MatrixMultiply
%.o	%.c
	${CC} ${CFLAGS} -g -c -o $@ $^
