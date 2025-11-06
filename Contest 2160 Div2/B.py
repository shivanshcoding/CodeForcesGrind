import sys
#input=lambda:sys.stdin.readline().rstrip()
 
for _ in range(int(input())):
  n=int(input())
  a=[0]+[*map(int,input().split())]
  res=[]
  for i in range(n):
    diff=a[i+1]-a[i]
    if i-diff>=0:
      res.append(res[i-diff])
    else:
      res.append(i+1)
  print(*res)