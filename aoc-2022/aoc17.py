#!/usr/bin/python3

import os
import sys
    
def main():
    with open(sys.argv[1]) as f:
        lines = f.read().splitlines()
    cmds = list(map(string_to_cmd, lines))
    tail_pos_set = {(0, 0)}

    head_pos = (0, 0)
    tail_pos = (0, 0)
    for cmd in cmds:
        head_pos, tail_pos = cmd(head_pos, tail_pos, tail_pos_set)
    
    print(len(tail_pos_set))

def string_to_cmd(s):
    s = s.split()
    cmd_dict = {"R": right, "L": left, "U": up, "D": down}
    return (lambda head_pos, tail_pos, tail_set: move(head_pos, tail_pos, cmd_dict[s[0]], int(s[1]), tail_set))

def move(head_pos, tail_pos, direction_fn, number, tail_pos_set):
    for i in range(number):
        head_pos = direction_fn(head_pos)
        x_diff = head_pos[0] - tail_pos[0]
        y_diff = head_pos[1] - tail_pos[1]
        if (x_diff == 0 and abs(y_diff) > 1) or (y_diff == 0 and abs(x_diff) > 1):
            tail_pos = direction_fn(tail_pos)
        elif (x_diff == 1 and abs(y_diff) > 1):
            tail_pos = direction_fn(right(tail_pos))
        elif (x_diff == -1 and abs(y_diff) > 1):
            tail_pos = direction_fn(left(tail_pos))
        elif (y_diff == 1 and abs(x_diff) > 1):
            tail_pos = direction_fn(up(tail_pos))
        elif (y_diff == -1 and abs(x_diff) > 1):
            tail_pos = direction_fn(down(tail_pos))
        tail_pos_set.add(tail_pos)
    return head_pos, tail_pos
            
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
