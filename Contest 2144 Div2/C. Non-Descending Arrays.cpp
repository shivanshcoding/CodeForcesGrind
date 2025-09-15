#include <bits/stdc++.h>
using namespace std;
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
using ll = long long;
const ll MOD = 998244353;

int n;
map<tuple<int,int,int>, ll> dp;

ll Ans(int i, int pa, int pb, vector<ll>& a, vector<ll>& b){
    if(i == n) return 1;

    auto key = make_tuple(i, pa, pb);
    if(dp.count(key)) return dp[key];

    ll ans = 0;
    if(b[i] >= pa && a[i] >= pb){
        ans = (ans + Ans(i+1, b[i], a[i], a, b)) % MOD;
    }
    if(a[i] >= pa && b[i] >= pb){
        ans = (ans + Ans(i+1, a[i], b[i], a, b)) % MOD;
    }
    return dp[key] = ans;
}

void solve() {
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    dp.clear();
    cout << Ans(0, 0, 0, a, b) << "\n";
}

int main() {
    fastio();
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
