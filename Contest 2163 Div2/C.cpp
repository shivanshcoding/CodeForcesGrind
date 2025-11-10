#include <bits/stdc++.h>
using namespace std;

#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pll = pair<ll, ll>;
const ll MOD = 1e9 + 7, INF = 1e18;

struct PrefixSuffix {
    vector<pll> pre, suf;
    int n;
    PrefixSuffix(const vector<vector<ll>>& g, int sz) : n(sz) {
        pre.resize(n);
        suf.resize(n);
        pre[0] = {g[0][0], g[0][0]};
        for (int i = 1; i < n; i++) {
            pre[i].f = max(pre[i - 1].f, g[0][i]);
            pre[i].s = min(pre[i - 1].s, g[0][i]);
        }
        suf[n - 1] = {g[1][n - 1], g[1][n - 1]};
        for (int i = n - 2; i >= 0; i--) {
            suf[i].f = max(suf[i + 1].f, g[1][i]);
            suf[i].s = min(suf[i + 1].s, g[1][i]);
        }
    }
};

struct RectangleUnion {
    int n;
    vector<vector<ll>> grid;
    RectangleUnion(int sz) : n(sz) {
        grid.assign(2, vector<ll>(n));
    }
    void read() {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
    }
    ll compute() {
        PrefixSuffix ps(grid, n);
        vector<ll> maxM(2 * n + 2, 0);
        for (int i = 0; i < n; i++) {
            ll big = max(ps.pre[i].f, ps.suf[i].f);
            ll small = min(ps.pre[i].s, ps.suf[i].s);
            maxM[big] = max(maxM[big], small);
        }
        ll ans = 0, cur = 0;
        for (int r = 1; r <= 2 * n; r++) {
            cur = max(cur, maxM[r]);
            ans += cur;
        }
        return ans;
    }
};

int main() {
    fastio();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        RectangleUnion solver(n);
        solver.read();
        cout << solver.compute() << "\n";
    }
    return 0;
}
