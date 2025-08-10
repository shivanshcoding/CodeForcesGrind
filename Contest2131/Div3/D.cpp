#include <bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define vec vector
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back
#define maxel(v) *max_element((v).begin(), (v).end())
#define minel(v) *min_element((v).begin(), (v).end())

typedef long long ll;

void solve() {
    int n;
    cin >> n;

    // adjacency list banate hain
    vec<vec<int>> adj(n + 1);
    vec<int> deg(n + 1, 0);

    // edges input lete hain
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++;
        deg[v]++;
    }

    // check karte hain ki graph star type ka hai ya nahi
    bool is_star = false;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == n - 1) { // agar ek node sabse connected hai
            is_star = true;
            break;
        }
    }
    if (is_star) {
        cout << 0 << endl;
        return;
    }

    vec<int> sz(n + 1);            // subtree ka size
    vec<int> leaves_down(n + 1);   // subtree me kitne leaf nodes hain
    vec<ll> ops_down(n + 1, 0);    // neeche se operations ka count

    // DFS function jo subtree size, leaves aur ops calculate karega
    function<void(int, int)> dfs1 = [&](int u, int p) {
        sz[u] = 1;
        leaves_down[u] = (deg[u] == 1); // agar leaf hai to 1
        ops_down[u] = 0;
        
        for (int v : adj[u]) {
            if (v == p) continue; // parent ko skip karo
            dfs1(v, u);
            sz[u] += sz[v];
            leaves_down[u] += leaves_down[v];
            if (sz[v] > 1) {
                ops_down[u] += leaves_down[v];
            }
        }
    };
    
    dfs1(1, 0);

    ll min_ops = -1;
    ll total_leaves = leaves_down[1]; // pure tree ke total leaves

    // har node ko root maan ke operations ka count nikalte hain
    for (int i = 1; i <= n; ++i) {
        ll current_ops = ops_down[i];
        if (i != 1) { // agar root nahi hai
            ll parent_comp_size = n - sz[i];
            if (parent_comp_size > 1) {
                current_ops += (total_leaves - leaves_down[i]);
            }
        }
        if (min_ops == -1 || current_ops < min_ops) {
            min_ops = current_ops;
        }
    }

    cout << min_ops << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
