
SIZE = 20

all: 
	make int   SIZE=${SIZE} CFLAGS="-O0 -Wall"
	make int   SIZE=${SIZE} CFLAGS="-O3 -Wall"
	make float SIZE=${SIZE} CFLAGS="-O0 -Wall"
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall"


int:
	time ./MatrixMultiply.py ${SIZE} int
#	gcc ${CFLAGS} -g -o MatrixMultiply MatrixMultiply.c -DNLINE=${SIZE} -DNCOL=${SIZE}
#	time ./MatrixMultiply
float:
	time ./MatrixMultiply.py ${SIZE} float
	gcc ${CFLAGS} -g -o MatrixMultiply MatrixMultiply.c -DNLINE=${SIZE} -DNCOL=${SIZE} -DTYPEELTFLT
	time ./MatrixMultiply
clean:
	rm MatrixMultiply
