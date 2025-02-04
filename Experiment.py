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

if __name__ == "__main__":
    import subprocess, os, sys, datetime, argparse
    p = argparse.ArgumentParser("Build FreeBSD world and kernel")
    p.add_argument("-l", "--numberOfLines",   nargs = 1, default=["100"],   help="Matrix #Line")
    p.add_argument("-c", "--numberOfColumns", nargs = 1, default=["200"],   help="Matrix #Column")
    p.add_argument("-d", "--dataType",        nargs = 1, default=["float"], help="Data type")
    a = p.parse_args()
    print (a)

    r = doCmd(["./MatrixMultiply.py", "--numberOfLines", a.numberOfLines[0], "--numberOfColumns", a.numberOfColumns[0], "--dataType", a.dataType[0]])
    print (r)
    reference = r.split(":")[4]
    reference = reference.split()[0]
    doCmd(["javac", "MatrixMultiply.java"])
    r = doCmd(["java", "MatrixMultiply", a.numberOfLines[0], a.numberOfColumns[0], str(reference)])
    print (r)
    r = doCmd(["./MatrixMultiply", a.numberOfLines[0], a.numberOfColumns[0], str(reference)])
    print (r)
