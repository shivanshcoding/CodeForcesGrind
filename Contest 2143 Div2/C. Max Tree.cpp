#include <bits/stdc++.h>
using namespace std;
struct custom_hash {
   static uint64_t splitmix64(uint64_t x) {
       x += 0x9e3779b97f4a7c15;
       x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
       x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
       return x ^ (x >> 31);
   }
size_t operator()(uint64_t x) const {
       static const uint64_t FIXED_RANDOM =
       chrono::steady_clock::now().time_since_epoch().count();
       return splitmix64(x + FIXED_RANDOM);
   }
};
#define prDouble(x) cout<<fixed<<setprecision(10)<<x
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using tll = tuple<ll,ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) indeg[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    // If topo.size() < n, graph had a cycle
    return topo;
}

void dfs(int i, int p, vector<vector<vector<int>>> &adj, vector<vector<int>> &adj2) {
    for (auto &edge : adj[i]) {
        int k = edge[0], x = edge[1], y = edge[2];
        if (k == p) continue;
        if(i>k){
            if (x > y) {
                adj2[i].push_back(k);
            } else {
                adj2[k].push_back(i);
            }
        }else{
            if (x > y) {
                adj2[k].push_back(i);
            } else {
                adj2[i].push_back(k);
            }
        }
        
        dfs(k, i, adj, adj2);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<vector<int>>> adj(n);   // 3D vector
    for (int i = 0; i < n - 1; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--, v--;
        adj[u].push_back({v, x, y});
        adj[v].push_back({u, x, y});
    }

    vector<vector<int>> adj2(n);          // DAG built from tree
    dfs(0, -1, adj, adj2);

    vector<int> order = topoSort(n, adj2);
    vector<int> ans(n);
    int curr = 1;
    for(int i: order){
        ans[i] = curr;
        curr++;
    }
    printv(ans);
    cout<<endl;
}


int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}