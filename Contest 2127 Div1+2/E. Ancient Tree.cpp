// #include<bits/stdc++.h>
// using namespace std;



// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int t;
//     cin>> t;
//     while(t--){
//         int n, k;
//         cin >> n >> k;
//         vector<int> w(n);
//         for(int i = 0; i < n; i++) {
//             cin >> w[i];
//         }
//         vector<int> c(n);
//         for(int i = 0; i < n; i++) {
//             cin >> c[i];
//         }
//         vector<vector<int>> adj(n);
//         for(int i = 0; i < n - 1; i++) {
//             int u, v;
//             cin >> u >> v;
//             u--; v--;
//             adj[u].push_back(v);
//             adj[v].push_back(u);
//         }
//         cout<<solve(adj,n,k,w,c)<<endl;
//         for(int curr: c){
//             cout<<curr<<" ";
//         }
//         cout<<endl;
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MXN = 2e5+1, LOG = 18;

int n, k, w[MXN], c[MXN], par[LOG][MXN], stt[MXN], timer, h[MXN], cnt[MXN], col[MXN];
vector<int> g[MXN], cols[MXN];
bool mark[MXN], cutie[MXN];

void dfs(int v) {
    stt[v] = timer++;
    for(int i=1; i<LOG; i++) par[i][v] = par[i-1][par[i-1][v]];
    for(int u : g[v])
        if(u!=par[0][v]) {
            h[u] = h[v]+1;
            par[0][u] = v;
            dfs(u);
        }
}

inline int jump(int v, int d) {
    for(int i=0; i<LOG; i++)
        if(d>>i&1)
            v = par[i][v];
    return v;
}

inline int LCA(int u, int v) {
    if(h[u]<h[v]) swap(u, v);
    u = jump(u, h[u]-h[v]);
    if(u==v) return u;
    for(int i=LOG-1; i>=0; i--)
        if(par[i][u]!=par[i][v])
            u = par[i][u], v = par[i][v];
    return par[0][u];
}

void DFS(int v, int cc) {
    if(c[v]) cc=c[v];
    else c[v]=cc;
    for(int u : g[v])
        if(u!=par[0][v])
            DFS(u, cc);
}

void Main() {
    cin >> n >> k;
    timer = 0;
    for(int i=1; i<=n; i++) {
        cnt[i] = 0;
        col[i] = 0;
        g[i].clear();
        cutie[i] = 0;
        cols[i].clear();
    }
    for(int i=1; i<=n; i++) cin >> w[i];
    for(int i=1; i<=n; i++) cin >> c[i], cols[c[i]].push_back(i);
    for(int i=1, u,v; i<n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bool fnd=0;
    for(int i=1; i<=n; i++)
        fnd |= c[i];
    if(!fnd) {
        cout << "0\n";
        for(int i=1; i<=n; i++) cout << "1 ";
        cout << '\n';
        return;
    }
    dfs(1);
    for(int i=1; i<=k; i++) {
        sort(cols[i].begin(), cols[i].end(), [&](int u, int v) {
            return stt[u]<stt[v];
        });
        vector<int> V;
        for(int j=0, u, v, lca; j+1<int(cols[i].size()); j++) {
            u = cols[i][j], v = cols[i][j+1], lca = LCA(u, v);
            if(!mark[lca]) {
                if(c[lca]) {
                    if(c[lca] != i) cutie[lca] = 1;
                    continue;
                }
                mark[lca] = 1;
                cnt[lca]++;
                col[lca] = i;
                V.push_back(lca);
            }
        }
        for(int v : V) mark[v] = 0;
        cols[i].clear();
    }
    ll val=0;
    for(int i=1; i<=n; i++) {
        if(cutie[i] || cnt[i]>1) val += w[i];
        if(!c[i] && cnt[i]==1) c[i] = col[i];
    }
    cout << val << '\n';
    for(int i=1; i<=n; i++)
        if(c[i]) {
            DFS(1, c[i]);
            break;
        }
    for(int i=1; i<=n; i++) cout << c[i] << ' ';
    cout << '\n';
}

int32_t main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int tc;
    cin >> tc;
    while(tc--) Main();
    return 0;
}