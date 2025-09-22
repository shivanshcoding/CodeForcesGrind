#include<bits/stdc++.h>
using namespace std;
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
int n;
int a[300005];
struct ds{
	int seg[1200005],tag[1200005];
	void build(int l,int r,int p){
		seg[p]=tag[p]=0;
		if(l==r)return;
		int m=(l+r)>>1;
		build(l,m,p*2+1);build(m+1,r,p*2+2);
	}
	void update(int l,int r,int s,int t,int p){
		if(l<=s&&t<=r){
			++seg[p];++tag[p];
			return;
		}
		int m=(s+t)>>1;
		if(m>=l)update(l,r,s,m,p*2+1);
		if(m<r)update(l,r,m+1,t,p*2+2);
		seg[p]=max(seg[p*2+1],seg[p*2+2])+tag[p];
	}
	void point(int pos,int l,int r,int p,int val=0){
		if(l==r)return seg[p]=-val,void();
		int m=(l+r)>>1;
		val+=tag[p];
		if(m>=pos)point(pos,l,m,p*2+1,val);
		else point(pos,m+1,r,p*2+2,val);
		seg[p]=max(seg[p*2+1],seg[p*2+2])+tag[p];
	}
}seg;
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i];
	seg.build(0,n,0);
	REP(i,0,n){
		seg.update(0,a[i],0,n,0);
		seg.point(a[i],0,n,0);
		cout<<seg.seg[0]<<' ';
	}
	cout<<'\n';
}
void TC() {
    int tc=1;
    cin>>tc;
	while(tc--){
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}