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
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1};
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

const int MAXN = 100005;
const int LOGN = 18;

int mu[MAXN];
int min_prime[MAXN];
vector<int> primes;
vector<int> divisors[MAXN];

int N;
vector<int> adj[MAXN];
int tin[MAXN], tout[MAXN], depth[MAXN];
int up[MAXN][LOGN];
int timer_count;
int LOG_VAL;

vector<int> sorted_multiples[MAXN];
vector<int> vt_adj[MAXN];
int mark[MAXN];
int vt_sz[MAXN];
ll S[MAXN];

void precompute(int max_n) {
    mu[1] = 1;
    for (int i = 2; i <= max_n; ++i) {
        if (min_prime[i] == 0) {
            min_prime[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (p > min_prime[i] || (long long)i * p > max_n) break;
            min_prime[i * p] = p;
            if (min_prime[i] == p) mu[i * p] = 0;
            else mu[i * p] = -mu[i];
        }
    }

    for (int i = 1; i <= max_n; ++i) {
        for (int j = i; j <= max_n; j += i) {
            divisors[j].push_back(i);
        }
    }
}

void build_lca(int root) {
    timer_count = 0;
    LOG_VAL = 1;
    while ((1 << LOG_VAL) <= N) LOG_VAL++;

    vector<pair<int, int>> st;
    st.reserve(N);
    st.push_back({root, 0});
    
    tin[root] = ++timer_count;
    depth[root] = 0;
    up[root][0] = root;
    
    while (!st.empty()) {
        int u = st.back().first;
        int& idx = st.back().second;
        
        if (idx == 0) {
            for (int j = 1; j < LOG_VAL; ++j) {
                up[u][j] = up[up[u][j-1]][j-1];
            }
        }
        
        if (idx < (int)adj[u].size()) {
            int v = adj[u][idx++];
            if (v == up[u][0]) continue;
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            tin[v] = ++timer_count;
            st.push_back({v, 0});
        } else {
            tout[u] = ++timer_count;
            st.pop_back();
        }
    }
}

inline bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LOG_VAL - 1; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

void solve(int t_case) {
    if (!(cin >> N)) return;

    for (int i = 1; i <= N; ++i) {
        adj[i].clear();
        S[i] = 0;
        sorted_multiples[i].clear();
    }

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build_lca(1);

    vector<int> p(N);
    iota(p.begin(), p.end(), 1);
    
    sort(p.begin(), p.end(), [](int a, int b) {
        return tin[a] < tin[b];
    });
    
    for (int u : p) {
        for (int d : divisors[u]) {
            sorted_multiples[d].push_back(u);
        }
    }

    vector<int> vt_nodes; vt_nodes.reserve(N);
    vector<int> st; st.reserve(N);

    for (int d = 1; d <= N; ++d) {
        const vector<int>& nodes = sorted_multiples[d];
        int m = nodes.size();
        if (m < 2) continue;

        vt_nodes.clear();
        st.clear();
        
        auto add_edge = [&](int par, int child) {
            vt_adj[par].push_back(child);
            vt_nodes.push_back(par);
            vt_nodes.push_back(child);
        };

        for(int u : nodes) mark[u] = 1;

        st.push_back(nodes[0]);
        vt_nodes.push_back(nodes[0]);

        for (size_t i = 1; i < nodes.size(); ++i) {
            int u = nodes[i];
            int l = lca(u, st.back());
            
            if (l != st.back()) {
                while (st.size() >= 2 && depth[st[st.size() - 2]] >= depth[l]) {
                    add_edge(st[st.size() - 2], st.back());
                    st.pop_back();
                }
                if (st.back() != l) {
                    int child = st.back();
                    st.pop_back();
                    vt_nodes.push_back(l);
                    add_edge(l, child);
                    st.push_back(l);
                }
            }
            st.push_back(u);
            vt_nodes.push_back(u);
        }
        
        while (st.size() >= 2) {
            add_edge(st[st.size() - 2], st.back());
            st.pop_back();
        }

        sort(vt_nodes.begin(), vt_nodes.end(), [](int a, int b) {
            return tin[a] < tin[b];
        });
        vt_nodes.erase(unique(vt_nodes.begin(), vt_nodes.end()), vt_nodes.end());

        for (int i = vt_nodes.size() - 1; i >= 0; --i) {
            int u = vt_nodes[i];
            int current_sz = (mark[u] ? 1 : 0);
            
            for (int v : vt_adj[u]) {
                current_sz += vt_sz[v];
                
                ll count_in = vt_sz[v];
                ll dist_uv = depth[v] - depth[u];
                S[d] += count_in * (m - count_in) * dist_uv;
            }
            vt_sz[u] = current_sz;
        }

        for (int u : vt_nodes) {
            vt_adj[u].clear();
            mark[u] = 0;
            vt_sz[u] = 0;
        }
    }

    cout << "Case #" << t_case << ":";
    for (int k = 1; k <= N; ++k) {
        ll ans = 0;
        for (int j = 1; k * j <= N; ++j) {
            if (mu[j] == 0) continue;
            ans += (ll)mu[j] * S[k * j];
        }
        cout << " " << ans;
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute(MAXN - 1);

    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            solve(i);
        }
    }
    return 0;
}
