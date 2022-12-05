# -*- coding: utf-8 -*-
"""
Created on Sun Dec  4 14:24:42 2022

@author: trhol
"""

def main(infile):
    with open(infile) as f:
        lines = f.readlines()
    assignments = process_lines(lines)
    redundant = list(filter(lambda pair: overlap(pair), assignments))
    print(len(redundant))
    
def process_lines(lines):
    pairs = list(map(lambda l: l.strip().split(","), lines))
    ret = []
    for pair in pairs:
        p = []
        for elf in pair:
            temp = elf.split("-")
            temp[0] = int(temp[0])
            temp[1] = int(temp[1])
            p.append(temp)
        ret.append(p)
    return ret

def overlap(pair):
    s1 = pair[0][0]
    f1 = pair[0][1]
    s2 = pair[1][0]
    f2 = pair[1][1]
    return (s1 <= s2 and f1 >= f2) or (s2 <= s1 and f2 >= f1)