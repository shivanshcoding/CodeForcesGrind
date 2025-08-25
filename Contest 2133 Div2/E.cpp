#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define all(x) x.begin(), x.end()
#define vecin(name, len) vector<int> name(len); for (auto &_ : name) cin >> _;
#define vecout(v) for (auto _ : v) cout << _ << " "; cout << endl;

const int MAXN = 200005;
vector<int> adj[MAXN];
int colour[MAXN];
vector<pair<int, int>> ans;
vector<int> leaves;
bool vis[MAXN];

void dfs(int node, int parent) {
    vector<int> children;
    for (auto a : adj[node])
        if (a != parent) {
            dfs(a, node);
            children.push_back(a);
        }
    int num_1_children = 0;
    bool any_2_children = false;
    for (auto child : children) {
        if (colour[child] == 1)
            num_1_children ++;
        else if (colour[child] == 2)
            any_2_children = true;
    }
    if (any_2_children || num_1_children >= 3) {
        colour[node] = 0;
        ans.push_back({2, node + 1});
        ans.push_back({1, node + 1});
    } else if (num_1_children == 2) {
        colour[node] = 2;
    } else {
        colour[node] = 1;
        if (num_1_children == 0)
            leaves.push_back(node);
    }
}

void dfs2(int node) {
    vis[node] = true;
    ans.push_back({1, node + 1});
    for (auto a : adj[node])
        if (colour[a] != 0 && !vis[a])
            dfs2(a);
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++)
        adj[i].clear(), vis[i] = false;
    for (int i = 0; i < n - 1; i ++) {
        int a, b; cin >> a >> b;
        a --; b --;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ans.clear();
    leaves.clear();
    dfs(0, -1);
    for (auto a : leaves)
        if (!vis[a])
            dfs2(a);
    cout << ans.size() << endl;
    for (auto a : ans)
        cout << a.first << " " << a.second << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tt = 1;

    cin >> tt;

    while (tt--) solve();
    return 0;
}