CCclang = clang
CCgcc9 = gcc9
SIZE = 150

all: 
	make py    SIZE=${SIZE} 
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall -DGEMMVARIANT=1" CC=${CCclang}
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall -DGEMMVARIANT=2" CC=${CCclang}
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall -DGEMMVARIANT=3" CC=${CCclang}

experiment:
	make py    SIZE=${SIZE} 
	make int   SIZE=${SIZE} CFLAGS="-O0 -Wall" CC=${CCclang}
	make int   SIZE=${SIZE} CFLAGS="-O3 -Wall" CC=${CCclang}
	make float SIZE=${SIZE} CFLAGS="-O0 -Wall" CC=${CCclang}
	make float SIZE=${SIZE} CFLAGS="-O3 -Wall" CC=${py}

py:
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
