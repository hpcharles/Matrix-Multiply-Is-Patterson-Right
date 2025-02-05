#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import time

random.seed(1234)
def errMsg (msg):
    print(msg)
    print("MatrixMultiply [Matrix Size] [float|int]")
    sys.exit(-1)

def createRandomIntMatrix(nLine, nColumn):
    maxVal = 1000
    matrix = []
    for i in range(nLine):
        matrix.append([random.randint(0, maxVal) for el in range(nColumn)])
    return matrix

def createRandomFloatMatrix(nLine, nColumn):
    maxVal = 1000
    matrix = []
    for i in range(nLine):
        matrix.append([random.uniform(0,maxVal) for el in range(nColumn)])
    return matrix

def printMatrix(matrix):
    for line in matrix:
        print ("\t".join(map(str,line)))

def standardMatrixProduct(A, B):
    nLines   = len(A)
    nColumns = len(B)
    C = [[0 for i in range(nLines)] for j in range(nLines)]
    for i in range(nLines):
        for j in range(nLines):
            for k in range(nColumns):
                C[i][j] += A[i][k] * B[k][j]
    return C

if __name__ == "__main__":
    import sys
    import subprocess, os, sys, datetime, argparse
    p = argparse.ArgumentParser("Build FreeBSD world and kernel")
    p.add_argument("-l", "--numberOfLines",   nargs = 1, default=[512],     help="Matrix #Line")
    p.add_argument("-c", "--numberOfColumns", nargs = 1, default=[512],     help="Matrix #Column")
    p.add_argument("-d", "--dataType",        nargs = 1, default=["float"], help="Data type")
    a = p.parse_args()

    (nLines, nColumns) = (int(a.numberOfLines[0]), int(a.numberOfColumns[0]))
    dataType =  a.dataType[0]
    if dataType == "float":
        A = createRandomFloatMatrix(nLines, nColumns)
        B = createRandomFloatMatrix(nColumns, nLines)
    elif dataType == "int":
        A = createRandomIntMatrix(nLines, nColumns)
        B = createRandomIntMatrix(nColumns, nLines)
    else:
        errMsg("Unknown datatype : %s"%dataType)
    timeStart = time.process_time()
    C = standardMatrixProduct(A, B)
    timeEnd = time.process_time()
    nOps = 2*nLines*nColumns*nLines
    print ("%10s : (%d x %d) : %5.2f (s) : %d (ops): %12.2f (flops)"%("Python", nLines, nColumns, timeEnd - timeStart, nOps, nOps/(timeEnd - timeStart)))
