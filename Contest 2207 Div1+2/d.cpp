#include <bits/stdc++.h>
 
#define f first
#define s second
#define pb push_back
 
typedef long long int ll;
typedef unsigned long long int ull;
using namespace std;
typedef pair<int,int> pii;

#define INF 1e9
 
vector<vector<int>> adj;
 
int N, K, V;
 
int dfs(int v, int p = -1) {
    int l1 = INF;
    int l2 = INF;
    for (int u : adj[v]) {
        if (u != p) {
            int guy = dfs(u, v);
            if (guy < l2) swap(l2, guy);
            if (l2 < l1) swap(l1, l2);
        }
    }
    if (l1 == INF) {
        return 0;
    } else if (l2 == INF) {
        return 1 + l1;
    } else {
        int s = 1 + l1;
        if (l1 + l2 < K) s = 0;
        return s;
    }
 
    // what
    return -1;
}
 
int main() {
    bool debug = 0;
	ios::sync_with_stdio(0);
    cin.tie(0);
 
    int T; cin >> T;
    while (T--) {
        cin >> N >> K >> V;
        adj = vector<vector<int>>(N+1);
        for (int i = 1; i < N; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        cout << (dfs(V) ? "NO" : "YES") << endl;
    }
 
    return 0;
}