#!/usr/bin/env python3


if __name__ == "__main__":
    dataSize = {
        "tiny":            (  "10",     "10"),
        "small":           ( "100",    "100"),
        "medium":          ( "500",    "500"),
        "large":           ("1000",   "1000"),
        "verylarge":       ("2000",   "2000"),
        "rectangularFlat": (  "10", "100000"),
        "bar":             (   "1","1000000"),
        "rectangularHigh": ("5000",     "16"),
        "line":            ("5000",      "1"),
    }
    GFLOPS = {
        # model name	: Intel(R) Core(TM) i5-8500 CPU @ 3.00GHz
        # stepping	: 10
        # microcode	: 0xf8
        # cpu MHz		: 3677.633
        # https://stackoverflow.com/questions/16038729/max-flops-for-matrix-multiplication-intel-amd-cpu
        # Max SP FLOPs/s = frequencey * 4 SSE(8AVX) * 2 (MAC) * number of cores (not HW threads
        "i5-8500":  3.6*4*2*6 ,
        "i7-8665U": 442.0,   # https://cpu-benchmark.org/fr/cpu/intel-core-i7-8665u/
    }
    import matplotlib.pyplot as p
    import matplotlib.lines as mlines
    import sys, math

    if len(sys.argv) < 1:
        print("Provide dataset results")
        sys.exit(-1)
    with open(sys.argv[1]) as fin:
        # print(fin)
        d = fin.read().split("\n")
    #    print(d)
    speedupDb = {} # {"00100x00100": {"Java": X}, ...
    gFlopsDb =  {}
    for matrixName in ("small", "medium", "large", "verylarge", "rectangularFlat", "bar", "rectangularHigh", "line"):
        pattern = "%05dx%05d"%(int(dataSize[matrixName][0]), int(dataSize[matrixName][1]))
        for line in d:
            if pattern in line:
                dataSet = line.split(';')
                (variant, gflops, speedup) = (dataSet[0], dataSet[4], dataSet[5])
                speedup = speedup.replace(",", ".")
                gflops = gflops.replace(",", ".")
                # print ("%s|%s|%s"%(variant, gflops, speedup))
                if pattern not in speedupDb : speedupDb[pattern] = {}
                if pattern not in gFlopsDb  : gFlopsDb[pattern] = {}
                speedupDb[pattern][variant] = speedup
                gFlopsDb [pattern][variant] = gflops
    print('Speedup')
    for k in speedupDb:
        print(k+":"+str(speedupDb[k]))
    print('GFlops')
    for k in gFlopsDb:
        print(k+":"+str(gFlopsDb[k]))
    fig, ax = p.subplots()
    lineStyle = '.-'
    for size in speedupDb:
        Y = [float(speedupDb[size][m]) for m in speedupDb[size]]
        X = [variant  for variant in speedupDb[size].keys()]
        # ax.annotate(str(Y[i]), (X[i]+10, Y[i]), fontsize=12)
        # ax.text(X[i], Y[i]+10, Y[i], fontsize=12)
        plot = ax.semilogy(X, Y, lineStyle, label = size)
        p.legend()
    fileName = sys.argv[1]+"-speedup.png"
    print ("Image saved in %s"%fileName)
    p.savefig(fileName)
    fig, ax = p.subplots()
    lineStyle = '.-'
    for size in gFlopsDb:
        Y = [float(gFlopsDb[size][m]) for m in gFlopsDb[size]]
        X = [variant  for variant in gFlopsDb[size].keys()]
        # ax.annotate(str(Y[i]), (X[i]+10, Y[i]), fontsize=12)
        # ax.text(X[i], Y[i]+10, Y[i], fontsize=12)
        plot = ax.plot(X, Y, lineStyle, label = size)
        p.legend()
    # Add maximum line
    # xmin, xmax = ax.get_xbound()
    # ymax = GFLOPS["i5-8500"]
    # ymin = GFLOPS["i5-8500"]
    # l = mlines.Line2D([xmin,xmax], [ymin,ymax])
    # ax.add_line(l)
    fileName = sys.argv[1]+"-GFLOPS.png"
    print ("Image saved in %s"%fileName)
    p.savefig(fileName)
#        ax = f.add_subplot(111)
