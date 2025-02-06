#!/usr/bin/env python3


if __name__ == "__main__":
    import matplotlib.pyplot as p
    import sys, math

    if len(sys.argv) < 1:
        print("Provide dataset ressults")
        sys.exit(-1)
    fig, ax = p.subplots()
    lineStyle = '.-'
    for fileName in sys.argv[1:]:
        with  open(fileName) as fin:
            print(fileName)
            d = fin.read().split("\n")
        Y = [float(m.split(";")[5]) for m in d if len(m) > 0]
        X = [m.split(";")[0] for m in d if len(m) > 0]
        # for i in range(len(X)):
        #     #ax.annotate(str(Y[i]), (X[i]+10, Y[i]), fontsize=12)
        #     ax.text(X[i], Y[i]+10, Y[i], fontsize=12)
        plot = ax.semilogy(X, Y, lineStyle, label = fileName)
        p.legend()
    p.show()
#        ax = f.add_subplot(111)
