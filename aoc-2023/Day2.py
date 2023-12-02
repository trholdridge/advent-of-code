import re
from collections import defaultdict

def main():
    with open("input2.txt") as f:
        input = f.read().splitlines()

    games = {}
    for line in input:
        split1 = re.split(": ", line)
        id = int(split1[0][5:])
        split2 = re.split("; ", split1[1])
        draws = []
        for draw in split2:
            split3 = re.split(", ", draw)
            drawdict = defaultdict(int)
            for color in split3:
                split4 = re.split(" ", color)
                drawdict[split4[1]] = int(split4[0])
            draws.append(drawdict)
        games[id] = draws

    print(sum([id for id in games.keys() if possible(games[id], 12, 13, 14)]))
    print(sum([power(games[id]) for id in games.keys()]))

def possible(draws, red, green, blue):
    for dict in draws:
        if (dict["red"] > red 
            or dict["green"] > green
            or dict["blue"] > blue):
            return False
    return True

def power(draws):
    red = max([d["red"] for d in draws])
    green = max([d["green"] for d in draws])
    blue = max([d["blue"] for d in draws])
    return red * green * blue

if __name__ == "__main__":
    main()