#!/usr/bin/python3

import os
import sys

def main():
    with open(sys.argv[1]) as f:
        signal = f.read()
    window = []
    for count, char in enumerate(signal):
        window.append(char)
        if len(window) > 14:
            del window[0]
            if len(window) == len(set(window)):
                print(count + 1)
                return count + 1

if __name__ == "__main__":
    main()
