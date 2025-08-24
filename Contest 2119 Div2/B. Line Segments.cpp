#include<iostream>
#include<algorithm>
using namespace std;
#define N 100010
#define int long long
int t,n,sx,sy,tx,ty,a[N];
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>sx>>sy>>tx>>ty;
		for(int i=1;i<=n;i++)
		 cin>>a[i];
		sort(a+1,a+n+1);
		int p=(sx-tx)*(sx-tx)+(sy-ty)*(sy-ty);
		if(p>a[n]*a[n])
		{
			int sum=0;
			for(int i=1;i<=n;i++)
			{
				sum+=a[i];
				if(sum*sum>=p)
				 break;
			}
			if(sum*sum>=p)
			 puts("Yes");
			else
			 puts("No");
		}
		else
		{
			int sum=a[n];
			for(int i=1;i<=n-1;i++)
			 sum-=a[i];
			if(sum<=0||sum*sum<=p)
			 puts("Yes");
			else
			 puts("No");
		}
	}
}