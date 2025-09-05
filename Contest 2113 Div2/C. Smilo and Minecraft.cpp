#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m, k;

// 2D prefix sum query
ll query(int x1, int y1, int x2, int y2, vector<vector<ll>>& pref) {
    // clamp indices inside grid
    x1 = max(0, x1); y1 = max(0, y1);
    x2 = min(n - 1, x2); y2 = min(m - 1, y2);
    if (x1 > x2 || y1 > y2) return 0;

    ll res = pref[x2][y2];
    if (x1 > 0) res -= pref[x1 - 1][y2];
    if (y1 > 0) res -= pref[x2][y1 - 1];
    if (x1 > 0 && y1 > 0) res += pref[x1 - 1][y1 - 1];
    return res;
}

void solve() {
    cin >> n >> m >> k;
    k--; // adjust because problem defines side length = 2k+1
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    // build prefix sum of golds
    vector<vector<ll>> pref(n, vector<ll>(m, 0));
    ll total_gold = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i][j] = (grid[i][j] == 'g');
            total_gold += (grid[i][j] == 'g');
            if (i > 0) pref[i][j] += pref[i - 1][j];
            if (j > 0) pref[i][j] += pref[i][j - 1];
            if (i > 0 && j > 0) pref[i][j] -= pref[i - 1][j - 1];
        }
    }

    ll mini = LLONG_MAX;
    bool found = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') { // only explode in empty cells
                found = true;
                int x1 = i - k, y1 = j - k;
                int x2 = i + k, y2 = j + k;
                ll lost = query(x1, y1, x2, y2, pref);
                mini = min(mini, lost);
            }
        }
    }

    if (!found) {
        cout << 0 << "\n";
        return;
    }
    cout << total_gold - mini << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}