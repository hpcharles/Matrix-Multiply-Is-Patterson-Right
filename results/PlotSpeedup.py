#!/usr/bin/env python3

if __name__ == "__main__":
    import matplotlib.pyplot as p
    import sys
    dataSets = ["i5-8500-100x100.data", "i5-8500-500x500.data", "i5-8500-1000x1000.data",]
    fig, ax = p.subplots()
    lineStyle = '.-'
    for fileName in dataSets:
        with  open(fileName) as fin:
            print(fileName)
            d = fin.read().split("\n")
        Y = [float(m.split(";")[5]) for m in d if len(m) > 0]
        X = [m.split(";")[0] for m in d if len(m) > 0]
        plot = ax.semilogy(X, Y, lineStyle, label = fileName)
        p.legend()
    p.show()
#        ax = f.add_subplot(111)
