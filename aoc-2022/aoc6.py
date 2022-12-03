# -*- coding: utf-8 -*-
"""
Created on Sat Dec  3 13:39:03 2022

@author: trhol
"""

def main(infile):
    with open(infile) as f:
        lines = f.readlines()
    rucksacks = list(map(lambda line: set(line.strip()), lines))
    commons = []
    for i in range(len(rucksacks)//3):
        j = i * 3
        common = rucksacks[j].intersection(rucksacks[j+1]).intersection(rucksacks[j+2])
        commons.append(priority(*common))
    print(sum(commons))

def priority(char):
    if char.islower():
        return ord(char) - 96
    else:
        return ord(char) - 38