#!/usr/bin/python3

import itertools
import os
import sys

def main():
    with open(sys.argv[1]) as f:
        lines = f.read().splitlines()
    stack_lines = list(itertools.takewhile(lambda line: line != "", lines))
    move_lines = lines[(len(stack_lines)+1):]

    stacks = make_stacks(stack_lines)
    make_moves(stacks, move_lines)
    for stack in stacks:
        print(stack[-1], end="")
    print()
    return

def make_stacks(lines):
    stacks = []
    for i in range((len(lines[-1]) + 1) // 4):
        stacks.append([])
    for line in reversed(lines[:-1]):
        for i in range(len(stacks)):
            if line[i * 4 + 1] != " ":
                stacks[i].append(line[i * 4 + 1])
    return stacks

def make_moves(stacks, lines):
    for line in lines:
        line = line.split()
        num_crates = int(line[1])
        from_stack = int(line[3]) - 1
        to_stack = int(line[5]) - 1
        for i in range(num_crates):
            stacks[to_stack].append(stacks[from_stack].pop())

if __name__ == "__main__":
    main()
