#!/usr/bin/python3

import os
import sys
from abc import ABC, abstractmethod

class Node(ABC):
    def __init__(self, name, size):
        self.name = name
        self.size = size

    def get_name(self):
        return self.name

    def get_size(self):
        return self.size

    @abstractmethod
    def is_dir(self):
        pass

class Directory(Node):
    def __init__(self, name, parent):
        super().__init__(name, 0)
        self.parent = parent
        self.children = []

    def add_child(self, child):
        print("Current directory: " + self.name)
        child = child.split()
        if child[1] not in map(lambda c: c.get_name(), self.children):
            print("Adding ", end="")
            if child[0] == "dir":
                print("directory: " + child[1])
                self.children.append(Directory(child[1], self))
            else:
                print("file: " + child[1])
                self.size += int(child[0])
                self.children.append(File(child[1], int(child[0])))

    def get_size(self):
        return self.size
    
    def is_dir(self):
        return True

    def get_parent(self):
        return self.parent

    def get_child_dirs(self):
        return list(filter(lambda c: c.is_dir(), self.children))
        
    def get_child(self, name):
        for child in self.children:
            if child.get_name() == name:
                return child

    def get_size_recursive(self):
        return self.size + sum([c.get_size_recursive() for c in self.get_child_dirs()])

class File(Node):
    def __init__(self, name, size):
        super().__init__(name, size)
        
    def is_dir(self):
        return False
    
def main():
    with open(sys.argv[1]) as f:
        lines = f.read().splitlines()

    c = commands_and_outputs(lines)
    filesystem = build_filesystem(c)
    small_directories = filter_filesystem(filesystem)

    print(sum(small_directories.values()))

def commands_and_outputs(lines):
    print("Processing commands... ", end="")
    result = []
    temp = []
    for line in lines:
        if line[0] == "$":
            if len(temp) > 0: result.append(temp)
            temp = [line[2:], []]
        else:
            temp[1].append(line)
    result.append(temp)
    print("Done")
    return result

def build_filesystem(commands):
    print("Building filesystem... ", end="")
    fs = Directory("/", None)  # this is our / directory
    current = fs
    for command in commands:
        if command[0][:2] == "cd":
            destination = command[0][3:]
            if destination == "/":
                current = fs
            elif destination == "..":
                current = current.get_parent()
            else:
                current = current.get_child(destination)
        elif command[0] == "ls":
            for line in command[1]:
                current.add_child(line)
    print("Done")
    return fs

def filter_filesystem(fs):
    print("Filtering filesystem... ", end="")
    size_dict = {}
    filter_filesystem_acc(fs, size_dict)
    print("Done")
    return size_dict

def filter_filesystem_acc(fs, acc):
    fs_size = fs.get_size_recursive()
    if fs_size <= 100000:
        acc[fs] = fs_size
    for child in fs.get_child_dirs():
        filter_filesystem_acc(child, acc)
    return acc
               
if __name__ == "__main__":
    main()
