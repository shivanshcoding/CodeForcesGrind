#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;

ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll a) {
    return qpow(a, MOD - 2);
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> al(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        al[u].push_back(v);
        al[v].push_back(u);
    }
    vector<int> vec, par(n);
    auto dfs = [&](auto&& dfs, int u, int p)->int {
        int s = 1;
        for(int v : al[u]) {
            if(v == p) continue;
            s += dfs(dfs, v, u);
        }
        par[u] = s & 1;
        if(par[u] == 0) {
            vec.push_back(s);
            return 0;
        }
        return s;
    };
    int tot = dfs(dfs, 0, -1);
    if(tot == 0) {
        tot = vec.back();
        vec.pop_back();
    }
    if((int) vec.size() == 0) {
        cout << 1 << '\n';
        return;
    }
    ll ans = 1;
    for(int i = 1; i < (int)vec.size(); i++) {
        ans = ans * i % MOD;
    }
    ll sum = 0;
    for(int i = 0; i < (int)vec.size(); i++) {
        ans = ans * vec[i] % MOD * vec[i] % MOD;
        sum = (sum + inv(vec[i])) % MOD;
    }
    cout << ans * sum % MOD * tot % MOD << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);
    int T = 1;
    cin >> T;
    while(T--) {
        solve();
    }
	return 0;
}