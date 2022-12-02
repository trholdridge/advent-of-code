#!/usr/bin/python3

import os
import sys

def main():
    with open(sys.argv[1]) as f:
        lines = f.readlines()
    rounds = list(map(lambda line: score(*(line.split())), lines))
    print(sum(rounds))
    return sum(rounds)

def score(you, outcome):
    you = ord(you) - 65
    outcome = (ord(outcome) - 88) * 3
    return outcome + mymove(you, outcome)

def mymove(you, outcome):
    if (outcome == 0):
        return ((you - 1) % 3) + 1  # loss
    elif (outcome == 3):
        return you + 1  # draw
    else:
        return ((you + 1) % 3) + 1  # win

if __name__ == "__main__":
    main()
