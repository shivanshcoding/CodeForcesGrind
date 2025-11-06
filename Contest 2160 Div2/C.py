import sys
#input=lambda:sys.stdin.readline().rstrip()
 
for _ in range(int(input())):
  n=f"{int(input()):b}"
  ans="NO"
  for i in range(1,64):
    if len(n)<=i:
      w=n.zfill(i)
      B=w==w[::-1]
      if i%2==1:
        B=B and w[i//2]=='0'
      if B:
        ans="YES"
  print(ans)