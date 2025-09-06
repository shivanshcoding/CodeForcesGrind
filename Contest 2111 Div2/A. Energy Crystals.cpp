#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
void solve(){
	int x;
	cin >> x;
	int ans = 0;
	int a1 = 0, a2 = 0, a3 = 0;
	while(min({a1, a2, a3}) < x){
		if (a1 <= a2 && a1 <= a3){
			a1 = min(a2, a3) * 2 + 1;
		}
		else if (a2 <= a1 && a2 <= a3){
			a2 = min(a1, a3) * 2 + 1;
		}
		else{
			a3 = min(a1, a2) * 2 + 1;
		}
		ans++;
	}
	cout << ans << '\n';
}
 
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	int tests = 1;
	cin >> tests;
	for (int test = 0; test < tests; test++){
		solve();
	}
	return 0;
}