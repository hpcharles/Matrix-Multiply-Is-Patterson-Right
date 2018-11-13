#!/usr/bin/python
# -*- coding: utf-8 -*-
import random
random.seed(1234)

def createRandomIntMatrix(n):
    maxVal = 1000 # I don't want to get Java / C++ into trouble
    matrix = []
    for i in xrange(n):
        matrix.append([random.randint(0,maxVal) for el in xrange(n)])
    return matrix

def createRandomFloatMatrix(n):
    maxVal = 1000 # I don't want to get Java / C++ into trouble
    matrix = []
    for i in xrange(n):
        matrix.append([random.uniform(0,maxVal) for el in xrange(n)])
    return matrix

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-i", dest="filename", default="2000.in",
     help="input file with two matrices", metavar="FILE")
(options, args) = parser.parse_args()

def printMatrix(matrix):
    for line in matrix:
        print "\t".join(map(str,line))

def standardMatrixProduct(A, B):
    n = len(A)
    C = [[0 for i in xrange(n)] for j in xrange(n)]
    for i in xrange(n):
        for j in xrange(n):
            for k in xrange(n):
                C[i][j] += A[i][k] * B[k][j]
    return C

if __name__ == "__main__":
    import sys
    if sys.argv[2] == "float":
        A = createRandomFloatMatrix(int(sys.argv[1]))
        B = createRandomFloatMatrix(int(sys.argv[1]))
    else:
        A = createRandomIntMatrix(int(sys.argv[1]))
        B = createRandomIntMatrix(int(sys.argv[1]))
    C = standardMatrixProduct(A, B)
#    printMatrix(C)
