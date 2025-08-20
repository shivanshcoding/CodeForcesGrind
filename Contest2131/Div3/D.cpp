#include <bits/stdc++.h>
using namespace std;

int solve() {
    int n;
    cin >> n;

    vector<vector<int>> g(n);
    vector<int> deg(n, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;  // 0-indexed
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    if (n <= 3) {
        return 0;
    }

    // count leaves
    int c1 = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) c1++;
    }

    // find the node with maximum leaf neighbors
    int mx = 0;
    for (int u = 0; u < n; u++) {
        int cnt = 0;
        for (int v : g[u]) {
            if (deg[v] == 1) cnt++;
        }
        mx = max(mx, cnt);
    }

    return c1 - mx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << solve() << "\n";
    }
    return 0;
}
