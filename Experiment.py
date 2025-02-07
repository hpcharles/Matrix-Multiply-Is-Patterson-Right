#!/usr/bin/env python3

def doCmd(cmdAndArgs, DoitAfficher = False, dir=None):
    if (DoitAfficher):
        if dir != None:
            print("-->cd %s"%(dir))
        print("-->%s"%(" ".join(cmdAndArgs)))
    process = subprocess.Popen(cmdAndArgs, cwd=dir, stdout=subprocess.PIPE, stderr=subprocess.STDOUT);
    data = process.stdout.read().decode("utf8")
    returncode = process.wait()
    if 0 == returncode:
        return data
    else:
        print("Error :")
        lines = data.split("\n")
        print ('\n'.join(lines[-20:-1]))
        sys.exit(-1)

def checkBinary(CC, JAVA, JAVAC):
    print (f"Check if {CC}, {JAVA} and {JAVAC} are installed :")
    doCmd (["which", CC], True)
    doCmd (["which", JAVAC], True)
    doCmd (["which", JAVA], True)
    print("")

dataSize = {
    "tiny":            (  "10",     "10"),
    "small":           ( "100",    "100"),
    "medium":          (" 500",    "500"),
    "large":           ("1000",   "1000"),
    "verylarge":       ("2000",   "2000"),
    "rectangularFlat": (  "10", "100000"),
    "bar":             (   "1","1000000"),
    "rectangularHigh": ("5000",     "16"),
    "line":            ("5000",      "1"),
 }


if __name__ == "__main__":
    import subprocess, os, sys, datetime, argparse, multiprocessing
    p = argparse.ArgumentParser("Build FreeBSD world and kernel")
    p.add_argument("-d", "--dataType",        nargs = 1, default=["float"], help="Data type")
    p.add_argument("-v", "--verbose",         action="store_true",          help="Print commands")
    p.add_argument("-n", "--matrixName",      nargs = 1, default=["small"], help="Matrix name: \n%s"%(dataSize.keys()))
    a = p.parse_args()
    print (a)

    (numberOfLines, numberOfColumns) = dataSize[a.matrixName[0]]
    checkBinary("gcc", "javac", "java")
    processorNumber = str(multiprocessing.cpu_count())

    cCompilation = ["gcc", "-O3", "-Wall", "-Werror", ]
    toBuild = { "clean":   ["rm", "-f", "MatrixMultiply", "MatrixMultiply.class", "MatrixMultiplyThreadParallel"],
                "buildC": cCompilation + ["-o", "MatrixMultiply", "MatrixMultiply.c", "MatrixUtils.c"],
                "buildCParallel": cCompilation + ["-o", "MatrixMultiplyThreadParallel", "MatrixMultiplyThreadParallel.c", "MatrixUtils.c"],
                "buildJava": ["javac", "MatrixMultiply.java"],}

    toRun = {
        "python": ["./MatrixMultiply.py", "--numberOfLines", numberOfLines, "--numberOfColumns", numberOfColumns, "--dataType", a.dataType[0]],
        "java":   ["java", "MatrixMultiply", numberOfLines, numberOfColumns],
        "c":      ["./MatrixMultiply", numberOfLines, numberOfColumns],
        "cparallel": ["./MatrixMultiplyThreadParallel", numberOfLines, numberOfColumns, processorNumber],
    }
    # Make clean & build binaries
    r = doCmd(toBuild["clean"], a.verbose)
    r = doCmd(toBuild["buildC"], a.verbose)
    r = doCmd(toBuild["buildCParallel"], a.verbose)
    r = doCmd(toBuild["buildJava"], a.verbose)

    # Run experiments
    r = doCmd(toRun["python"], a.verbose)
    print (r, end="")
    r = r.split ("\n")[1] # 2nd result line
    reference = r.split(";")[4] # 5th element
    reference = reference.split()[0]
    r = doCmd(toRun["java"]+[reference], a.verbose)
    print (r, end="")
    r = doCmd(toRun["c"]+[reference], a.verbose)
    print (r, end="")
    r = doCmd(toRun["cparallel"]+[reference], a.verbose)
    print (r, end="")
