#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int MOD = 998244353;

int modpow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return (int)r;
}

int n, m;
long long V;
vector<int> a;
vector<int> tin, low, isBridge;
vector<vector<pair<int,int>>> adj;
int timer_dfs;

void dfs_bridge(int u, int pe) {
    tin[u] = low[u] = ++timer_dfs;
    for (auto [v, id] : adj[u]) {
        if (id == pe) continue;
        if (!tin[v]) {
            dfs_bridge(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) isBridge[id] = 1;
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

void h(){
    cin >> n >> m >> V;
    a.assign(n, -1);
    for (int i = 0; i < n; ++i) cin >> a[i];
    adj.assign(n, {});
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        edges[i] = {u, v};
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    tin.assign(n, 0);
    low.assign(n, 0);
    isBridge.assign(m, 0);
    timer_dfs = 0;
    dfs_bridge(0, -1);

    vector<vector<int>> H(n);
    vector<int> inH(n, 0);
    for (int i = 0; i < m; ++i) if (!isBridge[i]) {
        auto [u,v] = edges[i];
        H[u].push_back(v);
        H[v].push_back(u);
        inH[u] = inH[v] = 1;
    }

    long long free_vars = 0;
    vector<int> vis(n, 0), color(n, -1);

    for (int s = 0; s < n; ++s) if (inH[s] && !vis[s]) {
        queue<int> q;
        vector<int> comp;
        bool bip = true;
        vis[s] = 1;
        color[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            comp.push_back(u);
            for (int v : H[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    bip = false;
                }
            }
        }
        if (!bip) {
            for (int v : comp) {
                if (a[v] != -1 && a[v] != 0) {
                    cout << 0 << endl;
                    return;
                }
            }
        } else {
            int fixed_val = -1;
            bool bad = false;
            for (int v : comp) if (a[v] != -1) {
                if (fixed_val == -1) fixed_val = a[v];
                else if (fixed_val != a[v]) { bad = true; break; }
            }
            if (bad) { cout << 0 << endl; return; }
            if (fixed_val == -1) ++free_vars;
        }
    }

    for (int i = 0; i < n; ++i) if (!inH[i]) {
        if (a[i] == -1) ++free_vars;
    }

    cout << modpow(V % MOD, free_vars) << endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;cin>>t;
    while(t--){
        h();
    }
    return 0;
}