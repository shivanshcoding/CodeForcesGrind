#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int tin[MAXN], sz[MAXN];
vector<int> order;
int n, q;

void dfs(int u) {
    tin[u] = (int)order.size();
    order.push_back(u);
    sz[u] = 1;
    for (int v : g[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        g[p].push_back(i);
    }
    // Sort children to ensure DFS visits smallest index first
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());

    dfs(1);

    while (q--) {
        int u, k;
        cin >> u >> k;
        if (k > sz[u]) {
            cout << -1 << "\n";
        } else {
            cout << order[tin[u] + k - 1] << "\n";
        }
    }
    return 0;
}
