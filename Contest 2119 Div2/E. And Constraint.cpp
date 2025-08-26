#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
struct stu{
	int x;
	ll dp;
};
int n,a[100007],b[100007];
vector<stu> f,g;
const ll inf=0x3f3f3f3f3f3f3f3f;
void Subt(){
	cin>>n;
	for(int i=1;i<n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	a[n]=0;
	f.clear();
	f.push_back((stu){0,0});
	for(int i=1;i<=n;i++){
		int x=0;
		g.clear();
		for(int j=30;j>=-1;j--){
			int y=x|a[i-1]|a[i];
			if(j!=-1) y|=(1<<j); 
			if(y>=b[i]){
				ll mn=inf;
				for(stu l:f){
					if((l.x&y)!=a[i-1]) continue;
					mn=min(mn,l.dp+y-b[i]);
				}
				if(mn<inf) g.push_back((stu){y,mn});
			}
			x|=((1<<j)&b[i]);
		}
		swap(f,g);
	}
	ll mn=inf;
	for(stu l:f) mn=min(mn,l.dp);
	if(mn<inf) cout<<mn<<endl;
	else cout<<-1<<endl;
	return;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
	cin>>T;
	while(T--) Subt();
}