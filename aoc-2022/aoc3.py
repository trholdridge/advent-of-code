#!/usr/bin/python3

import os
import sys

def main():
    with open(sys.argv[1]) as f:
        lines = f.readlines()
    rounds = list(map(lambda line: score(*(line.split())), lines))
    print(sum(rounds))
    return sum(rounds)

def score(you, me):
    you = ord(you) - 64
    me = ord(me) - 87
    return me + outcome(you, me)

def outcome(you, me):
    if (you == me):
        return 3  # draw
    elif ((you - me) % 3 == 1):
        return 0  # loss
    else:
        return 6  # win

if __name__ == "__main__":
    main()
