CC = clang
CC = gcc9
SIZE = 150

all: 
	make py    SIZE=${SIZE} 
	make int   SIZE=${SIZE} CFLAGS="-O0 -Wall"
	make int   SIZE=${SIZE} CFLAGS="-O3 -Wall"
	make float SIZE=${SIZE} CFLAGS="-O0 -Wall"
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall"


py:
	./MatrixMultiply.py ${SIZE} int
	./MatrixMultiply.py ${SIZE} float

int:
	${CC} ${CFLAGS} -g -o MatrixMultiply MatrixMultiply.c -DNLINE=${SIZE} -DNCOL=${SIZE} -DTYPEELT=2
	 ./MatrixMultiply
	-rm ./MatrixMultiply

double:
	${CC} ${CFLAGS} -g -o MatrixMultiply MatrixMultiply.c -DNLINE=${SIZE} -DNCOL=${SIZE} -DTYPEELT=3
	 ./MatrixMultiply
	-rm ./MatrixMultiply

float:
	${CC} ${CFLAGS} -g -o MatrixMultiply MatrixMultiply.c -DNLINE=${SIZE} -DNCOL=${SIZE} -DTYPEELT=1
	./MatrixMultiply
	-rm ./MatrixMultiply

clean:
	rm MatrixMultiply
