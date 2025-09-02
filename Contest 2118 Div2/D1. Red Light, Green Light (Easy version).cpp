#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll m, k; cin >> m >> k;
    vector<ll> p(m+1), d(m+1);
    for (int i = 1; i <= m; i++) cin >> p[i];
    for (int i = 1; i <= m; i++) cin >> d[i];
    map<ll, vector<ll>> mpl, mpr;
    map<ll, ll> traffic;
    for (int i = 1; i <= m; i++) {
        traffic[p[i]] = d[i];
        mpl[(d[i]+p[i])%k].emplace_back(p[i]);
        mpr[(((d[i]-p[i])%k)+k)%k].emplace_back(p[i]);
    }

    auto get_next_left = [&](ll pos, ll t) {
        ll val = (t + pos) % k;
        auto &vec = mpl[val];
        auto it = lower_bound(vec.begin(), vec.end(), pos);
        if (it == vec.begin()) return -1ll;
        it--;
        return *it;
    };

    auto get_next_right = [&](ll pos, ll t) {
        ll val = (((t - pos) % k) + k) % k;
        auto &vec = mpr[val];
        auto it = lower_bound(vec.begin(), vec.end(), pos+1);
        if (it == vec.end()) return -1ll;
        return *it;
    };

    map<pair<ll, ll>, bool> dp;

    int q; cin >> q;

    for (int i = 1; i <= q; i++) {
        ll x; cin >> x;
        ll dir = 1, t = 0;

        set<pair<ll, ll>> states;

        bool ok = false;
        if (traffic.count(x) && traffic[x] == 0) dir ^= 1;

        for (int it = 0; it < 2*m; it++) {

            ll y = dir ? get_next_right(x, t) : get_next_left(x, t);
            if (y == -1) {
                ok = true;
                break;
            } else {
                t += abs(y-x);
                x = y;
                dir ^= 1;
            }

            if (states.count({x, dir})) break;
            states.insert({x, dir});

            if (dp.count({x, dir})) {
                ok = dp[{x, dir}];
                break;
            }
        }

        for (auto [a, b] : states) {
            dp[{a, b}] = ok;
        }

        cout << (ok?"YES\n":"NO\n");
    }

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}