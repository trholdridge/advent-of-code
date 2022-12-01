#!/usr/bin/python3

import os
import sys

def main():
    with open(sys.argv[1]) as f:
        elves = []
        temp = []
        for line in f:
            if line == "\n":
                elves.append(temp)
                temp = []
            else:
                temp.append(int(line))
        elves.append(temp)

    elf_totals = list(map(lambda elf: sum(elf), elves))
    print("1: ", max(elf_totals))
    return elf_totals

if __name__ == "__main__":
    main()
