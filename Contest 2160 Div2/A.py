import sys

# input=lambda:sys.stdin.readline().rstrip()

for _ in range(int(input())):
    n = int(input())
    a = [*map(int, input().split())]
    for i in range(0, n + 1):
        if i not in a:
            print(i)
            break
