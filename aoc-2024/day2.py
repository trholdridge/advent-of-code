import sys

def main():
    with open(sys.argv[1]) as f:
        lines = f.read().split('\n')
    reports = [[int(x) for x in line.split()] for line in lines]

    p1(reports)
    p2(reports)

def p1(reports):
    print(sum(is_safe(r) for r in reports))

def p2(reports):
    print(sum(is_safe_2(r) for r in reports))

def is_safe_2(report):
    return is_safe(report) or any(is_safe(report[:i] + report[i + 1:]) for i in range(len(report)))

def is_safe(report):
    if len(report) <= 1:
        return True

    safe_fn = safe_increase if (report[0] < report[1]) else safe_decrease
    for i in range(len(report) - 1):
        if not safe_fn(report[i], report[i + 1]):
            return False
    return True

def safe_increase(x, y):
    return 1 <= (y - x) <= 3

def safe_decrease(x, y):
    return 1 <= (x - y) <= 3

if __name__ == "__main__":
    main()