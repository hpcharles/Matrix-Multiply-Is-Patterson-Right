#!/usr/bin/python
# -*- coding: utf-8 -*-
from optparse import OptionParser
import random

random.seed(1234)

def createRandomIntMatrix(n):
    maxVal = 1000 # I don't want to get Java / C++ into trouble
    matrix = []
    for i in range(n):
        matrix.append([random.randint(0,maxVal) for el in range(n)])
    return matrix

def createRandomFloatMatrix(n):
    maxVal = 1000 # I don't want to get Java / C++ into trouble
    matrix = []
    for i in range(n):
        matrix.append([random.uniform(0,maxVal) for el in range(n)])
    return matrix


def parseUserInput():
    dimension   = sys.argv[1]
    dataType    = sys.argv[2]
    return (dimension, dataType)

parser = OptionParser()
parser.add_option("-i", dest="filename", default="2000.in",
     help="input file with two matrices", metavar="FILE")
(options, args) = parser.parse_args()

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
        A = createRandomFloatMatrix(int(dimension))
        B = createRandomFloatMatrix(int(dimension))
    else:
        A = createRandomIntMatrix(int(dimension))
        B = createRandomIntMatrix(int(dimension))
    C = standardMatrixProduct(A, B)
#    printMatrix(C)
