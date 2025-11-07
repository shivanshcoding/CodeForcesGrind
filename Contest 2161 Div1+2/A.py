for i in range(int(input())):
    r,x,d,n = map(int, input().split())
    s = input()
    count = 0
    for c in s:
        if (c == '1'or r<x):
            count += 1
            r = max(0,r-d)
 
    print(count) 