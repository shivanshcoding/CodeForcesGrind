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

namespace GravitySim {

    vector<long long> val;
    vector<int> up, lowestChild, endLeaf;
    vector<bool> dead;
    vector<set<pair<long long, int>>> child;
    vector<vector<int>> graph;

    void formTree(int u, int p) {
        up[u] = p;
        for (int v : graph[u]) {
            if (v == p) continue;
            child[u].insert({val[v], v});
            formTree(v, u);
        }
    }

    void assignLeaf(int u) {
        if (child[u].empty()) {
            lowestChild[u] = -1;
            endLeaf[u] = u;
            return;
        }
        for (auto &[w, v] : child[u]) assignLeaf(v);
        int mc = child[u].begin()->second;
        lowestChild[u] = mc;
        endLeaf[u] = endLeaf[mc];
    }

    void runCase() {
        cin >> n >> q;
        val.assign(n + 1, 0);
        up.assign(n + 1, 0);
        lowestChild.assign(n + 1, -1);
        endLeaf.assign(n + 1, 0);
        dead.assign(n + 1, false);
        child.assign(n + 1, {});
        graph.assign(n + 1, {});

        for (int i = 1; i <= n; i++) cin >> val[i];
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        formTree(1, 0);
        assignLeaf(1);

        while (q--) {
            int b;
            cin >> b;
            if (dead[b]) {
                cout << -1 << '\n';
                continue;
            }

            int leaf = endLeaf[b];
            cout << leaf << '\n';
            dead[leaf] = true;

            int p = up[leaf];
            while (p) {
                int prev = endLeaf[p];
                if (child[p].count({val[leaf], leaf})) child[p].erase({val[leaf], leaf});
                int newMin = child[p].empty() ? -1 : child[p].begin()->second;
                lowestChild[p] = newMin;
                int newLeaf = (newMin == -1) ? p : endLeaf[newMin];
                if (newLeaf == prev) break;
                endLeaf[p] = newLeaf;
                p = up[p];
            }
        }
    }

} 

int main() {
    fastio();

    cin >> t;
    while (t--) GravitySim::runCase();
    return 0;
}
