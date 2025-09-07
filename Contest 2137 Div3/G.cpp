#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct GraphGame {
    int n, m, q;
    vector<vector<int>> g, rg;
    vector<int> indeg, outdeg;
    vector<int> active, gone, locked, need;
    
    GraphGame(int nodes, int edges) {
        n = nodes;
        m = edges;
        g.assign(n+1, {});
        rg.assign(n+1, {});
        indeg.assign(n+1, 0);
        outdeg.assign(n+1, 0);
        active.assign(n+1, 0);
        gone.assign(n+1, 0);
        locked.assign(n+1, 0);
        need.assign(n+1, 0);
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
        outdeg[u]++;
        indeg[v]++;
    }

    void prepare() {
        // topological order
        deque<int> dq;
        for(int i=1;i<=n;i++) if(indeg[i]==0) dq.push_back(i);
        vector<int> order;
        while(!dq.empty()) {
            int u = dq.front(); dq.pop_front();
            order.push_back(u);
            for(auto v: g[u]) {
                if(--indeg[v]==0) dq.push_back(v);
            }
        }
        reverse(order.begin(), order.end());

        for(int u: order) {
            if(outdeg[u]==0) {
                active[u] = 1;
            } else {
                int cnt = 0;
                for(auto v: g[u]) if(locked[v]==0) cnt++;
                need[u] = cnt;
                if(cnt > 0) active[u] = 1;
            }
            if(!active[u]) {
                for(auto p: rg[u]) locked[p]++;
            }
        }
    }

    void removeNode(int u) {
        if(gone[u]) return;
        gone[u] = 1;

        deque<int> dq;
        vector<char> inq(n+1, 0);

        if(locked[u]==0) {
            for(auto p: rg[u]) {
                if(--need[p]==0 && active[p]) {
                    active[p] = 0;
                    if(!inq[p]) dq.push_back(p), inq[p]=1;
                }
            }
        }
        if(active[u]) {
            active[u] = 0;
            if(!inq[u]) dq.push_back(u), inq[u]=1;
        }

        while(!dq.empty()) {
            int cur = dq.front(); dq.pop_front();
            for(auto p: rg[cur]) {
                if(++locked[p]==1 && !gone[p]) {
                    for(auto gp: rg[p]) {
                        if(--need[gp]==0 && active[gp]) {
                            active[gp] = 0;
                            if(!inq[gp]) dq.push_back(gp), inq[gp]=1;
                        }
                    }
                }
            }
        }
    }

    bool isAlive(int u) {
        return active[u];
    }
};

void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    GraphGame gg(n,m);
    for(int i=0;i<m;i++) {
        int u,v; cin >> u >> v;
        gg.addEdge(u,v);
    }
    gg.prepare();
    while(q--) {
        int type, u;
        cin >> type >> u;
        if(type==1) gg.removeNode(u);
        else cout << (gg.isAlive(u) ? "YES\n" : "NO\n");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}
