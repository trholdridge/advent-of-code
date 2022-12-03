# -*- coding: utf-8 -*-
"""
Created on Sat Dec  3 13:17:17 2022

@author: trhol
"""

def main(infile):
    with open(infile) as f:
        lines = f.readlines()
    rucksacks = list(map(lambda line: process_line(line), lines))
    commons = list(map(lambda sack: sack[0].intersection(sack[1]), rucksacks))
    commons = list(map(lambda intersection: priority(*intersection), commons))
    print(sum(commons))
    
def process_line(line):
    split = [line[:len(line)//2], line[len(line)//2:]]
    split[0] = set(split[0])
    split[1] = set(split[1])
    return split

def priority(char):
    if char.islower():
        return ord(char) - 96
    else:
        return ord(char) - 38