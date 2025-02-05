CCclang = clang
CCgcc9 = gcc9
CFLAGS=-O3 -Wall -Werror -g
JAVAC=javac
# Binary files
FILES=MatrixMultiply.class MatrixMultiply MatrixMultiplyThreadParallel

all: small

# do Experiments
small:
	make clean do NLINES=100    NCOLUMNS=100

medium:
	make clean do NLINES=500    NCOLUMNS=500

large:
	make clean do NLINES=1000   NCOLUMNS=1000

verylarge:
	make clean do NLINES=4000   NCOLUMNS=4000

rectangularFlat: ${FILES}
	make clean do NLINES=10     NCOLUMNS=100000

rectangularHigh: ${FILES}
	make clean do NLINES=5000 NCOLUMNS=16

all:
	make small medium large verylarge rectangularFlat rectangularHigh

do: ${FILES}
	./Experiment.py  --numberOfLines ${NLINES} --numberOfColumns ${NCOLUMNS}

# Generate "binary" files
MatrixMultiply.class: MatrixMultiply.java
	${JAVAC} $<

MatrixMultiply: MatrixMultiply.c MatrixUtils.c
	${CC} ${CFLAGS} $^ -o $@

MatrixMultiplyThreadParallel: MatrixMultiplyThreadParallel.c MatrixUtils.c
	${CC} ${CFLAGS} $^ -o $@

clean:
	-rm MatrixMultiply MatrixMultiply.class MatrixMultiplyThreadParallel
