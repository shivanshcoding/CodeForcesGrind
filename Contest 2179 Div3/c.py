for test_case in range(int(input())):
    n = int(input())
    a = sorted([int(_) for _ in input().split()])
    print(max(a[0], a[1]-a[0]))