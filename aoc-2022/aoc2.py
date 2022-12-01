#!/usr/bin/python3

import os
import sys
import aoc1

def main():
    elf_totals = aoc1.main()
    elf_totals.sort()
    top_three = elf_totals[-3:]
    print("2: ", sum(top_three))

if __name__ == "__main__":
    main()
