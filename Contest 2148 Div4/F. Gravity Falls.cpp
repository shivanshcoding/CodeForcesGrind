#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define pb push_back
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define ROF(i,a,b) for(int i = (a); i >= (b); --i)
#define trav(a,x) for(auto& a: x)
#define sz(x) (int)x.size()
template<class T> bool ckmax(T& a, const T& b){return a<b?a=b,1:0;}
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) {for(auto &x : a) out << x << ' '; return out;};
 
void solve() {
	int n; cin >> n;
	vector<vector<int>> g(n), relevant;
	int max_k = 0;
	FOR(i,0,n){
		int k; cin >> k;
		g[i].resize(k);
		ckmax(max_k, k);
		FOR(j,0,k){
			cin >> g[i][j];
			if(sz(relevant) == j) relevant.pb({});
			relevant[j].pb(i);
		}
	}
	vector<int> lex_min(max_k), rank(n, -1);
	ROF(i,max_k-1,0){
		vector<array<int, 3>> cur;
		trav(j, relevant[i]){
			cur.pb({g[j][i], rank[j], j});
		}
		sort(all(cur));
		lex_min[i] = cur[0][2];
		int rk = 0;
		trav(j, cur) rank[j[2]] = rk++;
	}
	vector<int> ans;
	while(sz(ans) < max_k){
		int tmp = sz(ans);
		auto& v = g[lex_min[tmp]];
		FOR(i,tmp,sz(v)) ans.pb(v[i]);
	}
	assert(sz(ans) == max_k);
	cout << ans << "\n";
}
 
signed main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t = 1;
	cin >> t;
	for(int test = 1; test <= t; test++){
		solve();
	}
}