#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 1111111;
const LL inf = 1e18;
int n,k,a[N];
LL s[N];
int main(){
	int T,i,l,r,h;
	LL x,y,z,o,p,t;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(i=1;i<=n;i++)
			scanf("%d",a+i);
		sort(a+1,a+n+1);
		for(i=1;i<=n;i++)
			s[i]=s[i-1]+a[i];
		z=inf,o=-1;
		l=0,r=N;
		while(l<=r){
			h=l+r>>1;
			i=lower_bound(a+1,a+n+1,h)-a-1;
			x=(LL)i*h-s[i];
			i=lower_bound(a+1,a+n+1,h+k)-a-1;
			y=(s[n]-s[i])-(LL)(n-i)*(h+k);
			if(z>max(x,y))
				z=max(x,y),o=h;
			if(x<y)
				l=h+1;
			else
				r=h-1;
		}
		//cout<<z<<' '<<o<<endl;
		p=z*k;
		t=0;
		for(i=1;i<=n;i++){
			x=min(max((LL)a[i],o),o+k);
			p+=(LL)x*(x+1)/2;
			t+=x-a[i];
		}
		if(t>0)
			p-=(o+k)*t;
		if(t<0)
			p+=(o+1)*-t;
		printf("%lld\n",p);
	}
	return 0;
}