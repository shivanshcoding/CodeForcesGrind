#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> downPath; // longest downward path from each node
vector<ll> ans;

void dfs1(const vector<vector<int>>& adj, int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(adj, v, u);
        downPath[u] = max(downPath[u], 1 + downPath[v]);
    }
}

void dfs2(const vector<vector<int>>& adj, int u, int p, ll upPath, ll &diameter) {
    ll max1 = -1, max2 = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (downPath[v] > max1) {
            max2 = max1;
            max1 = downPath[v];
        } else if (downPath[v] > max2) {
            max2 = downPath[v];
        }
    }

    // diameter passing through u (two child paths)
    ll op1 = (max1 >= 0 && max2 >= 0) ? max1 + max2 + 2 : max1 + 1; // if one child, only one side
    // diameter using upPath
    ll op2 = (max1 >= 0 ? max1 + 1 : 0) + upPath;

    diameter = max({diameter, op1, op2});

    // For leaf or isolated node
    if ((int)adj[u].size() <= 1) {
        ans[u] = max(op1, op2) + 1; // +1 for new node connection
    }

    for (int v : adj[u]) {
        if (v == p) continue;
        ll use = (downPath[v] == max1 ? max2 : max1);
        dfs2(adj, v, u, max(upPath, (use >= 0 ? use + 1 : 0)) + 1, diameter);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ans.assign(n, 0);
    downPath.assign(n, 0);

    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    dfs1(adj, 0, -1);
    ll diameter = 0;
    dfs2(adj, 0, -1, 0, diameter);

    for (auto &x : ans) {
        cout << max(x, diameter) << "\n";
    }
}
