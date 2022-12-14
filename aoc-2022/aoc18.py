#!/usr/bin/python3

import os
import sys
    
def main():
    with open(sys.argv[1]) as f:
        lines = f.read().splitlines()
    cmds = list(map(string_to_cmd, lines))
    tail_pos_set = {(0, 0)}

    knots = [(0, 0) for i in range(10)]
    for cmd in cmds:
        cmd(knots, tail_pos_set)

    #print(plot(tail_pos_set))
    print(len(tail_pos_set))

def string_to_cmd(s):
    s = s.split()
    cmd_dict = {"R": right, "L": left, "U": up, "D": down}
    return (lambda knots, tail_set: move(knots, cmd_dict[s[0]], int(s[1]), tail_set))

def move(knots, direction_fn, number, tail_pos_set):
    for i in range(number):
        knots[0] = direction_fn(knots[0])
        for j in range(len(knots) - 1):
            knots[j+1] = follow(knots[j], knots[j+1])
        #print(knots)
        tail_pos_set.add(knots[-1])

def follow(head, tail):
    x_diff = head[0] - tail[0]
    y_diff = head[1] - tail[1]
    if abs(x_diff) > 1:
        return (tail[0] + (x_diff // 2), tail[1] + y_diff)
    elif abs(y_diff) > 1:
        return (tail[0] + x_diff, tail[1] + (y_diff // 2))
    else:
        return tail

def plot(tail_set):
    xes = list(map(lambda t: t[0], tail_set))
    ys = list(map(lambda t: t[1], tail_set))
    print(min(xes), min(ys))
    plot = ""
    for row in reversed(range(min(ys), max(ys) + 1)):
        for col in range(min(xes), max(xes) + 1):
            if (col, row) in tail_set:
                plot += "#"
            else:
                plot += "."
        plot += "\n"
    return plot
        
def right(pos):
    return (pos[0] + 1, pos[1])

def left(pos):
    return (pos[0] - 1, pos[1])

def up(pos):
    return (pos[0], pos[1] + 1)

def down(pos):
    return (pos[0], pos[1] - 1)

if __name__ == "__main__":
    main()
