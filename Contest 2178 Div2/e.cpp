// By Auchenai01
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
const ll MOD = 998244353;
const ll MAXX = 1e16;
const int INF = 1e9 + 7;
ll query(int l, int r) {
	cout << "? " << l + 1 << " " << r + 1 << endl;
	ll res;
	cin >> res;
	return res;
}
void solve() {
    int n;
    cin >> n;
    ll cur = query(0, n - 1);
    int pl = 0;
    int pr = n - 1;
    while (pl != pr) {
	    int l = pl;
	    int r = pr;
    	while (1) {
	    	int m = (l + r) / 2;
	    	ll X = query(pl, m);
	    	if (X == cur / 2) {
	    		cur = X;
	    		if (m - pl >= pr - (m + 1)) {
	    			pl = m + 1;
	    		} else {
	    			pr = m;
	    		}
	    		break;
	    	} else if (X > cur / 2) {
	    		r = m - 1;
	    	} else {
	    		l = m + 1;
	    	}
	    } 
    }
    ll Y = query(pl, pr);
    cout << "! " << Y << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}