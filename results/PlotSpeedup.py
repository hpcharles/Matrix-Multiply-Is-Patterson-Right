#!/usr/bin/env python3

if __name__ == "__main__":
    import matplotlib.pyplot as p
    import sys
    dataSets = ["i5-8500-00100x00100.data",
                "i5-8500-00500x00500.data",
                "i5-8500-01000x01000.data",
#                "i5-8500-04000x04000.data",
                "i5-8500-00010x10000.data",
                "i5-8500-05000x00016.data",
                ]
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
