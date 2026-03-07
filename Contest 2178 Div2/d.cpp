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
void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
    	cin >> a[i].first;
    	a[i].second = i;
    }
    if (m > n / 2) {
    	cout << -1 << endl;
    	return;
    }

    vector<pii> ans;
    auto print = [&] () {
    	cout << ans.size() << endl;
	    for (auto [x, y] : ans) {
	    	cout << x + 1 << " " << y + 1 << endl;
	    }
    };
    sort(a.begin(), a.end(), greater<>());
    if (m == 0) {
    	ll x = a[0].first;
    	ll summ = 0;
    	for (int i = 1; i < n; i++) {
    		summ += a[i].first;
    		if (summ >= x) {
    			for (int j = i + 1; j < n; j++) {
    				ans.push_back({a[j].second, a[j-1].second});
    			}
    			reverse(ans.begin(), ans.end());
    			for (int j = i; j >= 1; j--) {
    				ans.push_back({a[j].second, a[0].second});
    			}
    			print();
    			return;
    		}
    	}
		cout << -1 << endl;
		return;
    } else {
    	for (int i = 0; i < m; i++) {
    		ans.push_back({a[i].second, a[i + m].second});
	    }
	    for (int i = 2 * m - 1; i < n - 1; i++) {
	    	ans.push_back({a[i].second, a[i + 1].second});
	    }
	    reverse(ans.begin(), ans.end());
    }
    print();
    
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