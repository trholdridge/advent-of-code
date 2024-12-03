import numpy as np
import sys

def main():
    with open(sys.argv[1]) as f:
        lines = f.readlines()

    list1 = np.zeros(len(lines))
    list2 = np.zeros(len(lines))
    for i, line in enumerate(lines):
        item1, item2 = line.split()
        list1[i] = item1
        list2[i] = item2

    p1(list1, list2)
    p2(list1, list2)

def p1(list1, list2):
    sort1 = np.sort(list1)
    sort2 = np.sort(list2)
    print(sum(abs(sort1 - sort2)))

def p2(list1, list2):
    similarity = np.vectorize(lambda n: n * np.count_nonzero(list2 == n))
    print(sum(similarity(list1)))

if __name__ == "__main__":
    main()