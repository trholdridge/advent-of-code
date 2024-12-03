import re
import sys

def main():
    with open(sys.argv[1]) as f:
        inp = f.read()
    matches = re.findall('mul\(\d\d?\d?,\d\d?\d?\)|do\(\)|don\'t\(\)', inp)

    sum = 0
    do = True
    for match in matches:
        if match[:3] == 'do(':
            do = True
        elif match[:3] == 'don':
            do = False
        elif do:
            tok = re.split('\(|,|\)', match)
            sum += int(tok[1]) * int(tok[2])
    
    print(sum)

if __name__ == "__main__":
    main()