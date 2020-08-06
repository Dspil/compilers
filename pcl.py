#!/usr/bin/env python3
import sys
import argparse
from subprocess import Popen, PIPE, STDOUT, run
import textwrap

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = "A compiler for the PCL programming language", prog='./pcl', epilog="Exactly one of the following arguments must be present: program, -f, -i")
    parser.add_argument(
        "-O", "--optimize", help="Optimize program", action="store_true"
    )
    parser.add_argument(
        "-x", "--createex", help="Used only when [program] is given as argument. Create executable with program's filename without the extension", action="store_true"
    )
    parser.add_argument(
        "-f",
        "--outfinal",
        help="Program in stdin, assembly at stdout",
        action="store_true",
    )
    parser.add_argument(
        "-i",
        "--outllvmir",
        help="Program in stdin, llvm ir at stdout",
        action="store_true",
    )
    parser.add_argument("program", nargs="?", default="", help="Pcl program. Filename must have an extension")
    args = parser.parse_args()
    if sum([args.outfinal, args.outllvmir, len(args.program) > 0]) != 1:
        print(
            "You can only give exactly one of the following arguments:\n\tprogram\n\t-f, --outfinal\n\t-i, --outllvmir"
        )
        sys.exit(1)

    if len(args.program) > 0:
        try:
            with open(args.program, "r") as fhandle:
                pclinput = fhandle.read()
        except FileNotFoundError:
            print("File '{}' not found".format(args.program))
            sys.exit(1)
    else:
        pclinput = sys.stdin.read()

    try:
        if args.optimize:
            p = Popen(["./pclcomp", "flag"], stdout=PIPE, stdin=PIPE, stderr=PIPE)
        else:
            p = Popen(["./pclcomp"], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    except FileNotFoundError:
        print("Pcl executable not found. Run make at the pcl compiler directory")
        sys.exit(1)
    pout = p.communicate(input=pclinput.encode())
    if p.returncode == 1:
        print(pout[1].decode())
        sys.exit(1)
    llvmir = pout[0]
    if args.outllvmir:
        print(llvmir.decode())
        sys.exit(0)

    if args.optimize:
        p = Popen(["llc", "-O2"], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    else:
        p = Popen(["llc"], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    pout = p.communicate(input=llvmir)
    if p.returncode == 1:
        print(pout[1].decode())
        sys.exit(1)
    asm = pout[0].decode()
    if args.outfinal:
        print(asm)
        sys.exit(0)

    fname = args.program.split(".")[0]
    intermediate = "{}.imm".format(fname)
    final = "{}.asm".format(fname)
    with open(intermediate, "w") as fhandle:
        fhandle.write(llvmir.decode())
    with open(final, "w") as fhandle:
        fhandle.write(asm)
    if args.createex:
        run(["clang", final, "builtins.so", "-lm", "-o", fname])
