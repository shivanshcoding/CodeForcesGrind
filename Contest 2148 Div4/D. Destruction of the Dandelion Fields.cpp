#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    vector<int> p[2];
    for (int i : a) p[i%2].push_back(i);
    long long ans = 0;
    if (p[1].size()) ans += accumulate(p[0].begin(), p[0].end(), 0LL);
    sort(p[1].rbegin(), p[1].rend());
    int m = p[1].size();
    for (int i = 0; i < (m+1)/2; i++) ans += p[1][i];
    cout << ans << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
}