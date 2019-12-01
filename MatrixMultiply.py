#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import time

random.seed(1234)
def errMsg (msg):
    print(msg)
    print("MatrixMultiply [Matrix Size] [float|int]")
    sys.exit(-1)

def createRandomIntMatrix(n):
    maxVal = 1000 
    matrix = []
    for i in range(n):
        matrix.append([random.randint(0,maxVal) for el in range(n)])
    return matrix

def createRandomFloatMatrix(n):
    maxVal = 1000 
    matrix = []
    for i in range(n):
        matrix.append([random.uniform(0,maxVal) for el in range(n)])
    return matrix

def parseUserInput():
    try:
        dimension   = int(sys.argv[1])
        dataType    = sys.argv[2]
        return (dimension, dataType)
    except IndexError:
        errMsg ("Give arguments !")
def printMatrix(matrix):
    for line in matrix:
        print ("\t".join(map(str,line)))

def standardMatrixProduct(A, B):
    n = len(A)
    C = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]
    return C

if __name__ == "__main__":
    import sys

    (dimension, dataType) = parseUserInput()
    if dataType == "float":
        A = createRandomFloatMatrix(dimension)
        B = createRandomFloatMatrix(dimension)
    elif dataType == "int":
        A = createRandomIntMatrix(dimension)
        B = createRandomIntMatrix(dimension)
    else:
        errMsg("Unknown datatype : %s"%dataType)
    timeStart = time.process_time()
    C = standardMatrixProduct(A, B)
    timeEnd = time.process_time()
    Nops = 2*dimension*dimension*dimension
    print ("Elapsed time (s) %f"%(timeEnd - timeStart))
    print ("Ops              %d (%s)"%(Nops, dataType))
    print ("Flops            %d "%(Nops/(timeEnd - timeStart)))


