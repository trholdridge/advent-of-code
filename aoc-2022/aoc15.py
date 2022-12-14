#!/usr/bin/python3

import numpy as np
import os
import sys
    
def main():
    with open(sys.argv[1]) as f:
        lines = f.read().splitlines()
    tree_grid = np.array([list(line) for line in lines])
    print(tree_grid)
               
if __name__ == "__main__":
    main()
