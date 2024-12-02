# -*- coding: utf-8 -*-
"""
Created on Sun Dec 11 13:42:31 2022

@author: trhol
"""

def main(infile):
    with open(infile) as f:
        lines = f.read().splitlines()
    
    cycle = 1
    i = 0
    signal = 1
    important_signals = 0
    add = False
    while(i < len(lines)):
        if (cycle + 20) % 40 == 0:
            important_signals += (signal * cycle)
        if add:
            signal += int(lines[i][5:])
            i += 1
            add = False
        elif lines[i][:4] == "addx":
            add = True
        elif lines[i] == "noop":
            i += 1
        cycle += 1
    
    return important_signals