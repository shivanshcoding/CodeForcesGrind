#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long c;
    long long cost; // current cost of this edge
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> color(n + 1);
        for (int i = 1; i <= n; ++i) cin >> color[i];

        vector<Edge> edges;
        vector<vector<int>> incident(n + 1); // incident edges for each node

        long long total = 0;

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            long long c;
            cin >> u >> v >> c;

            long long cost = (color[u] == color[v]) ? 0 : c;
            edges.push_back({u, v, c, cost});
            total += cost;

            incident[u].push_back(i);
            incident[v].push_back(i);
        }

        while (q--) {
            int vtx, newColor;
            cin >> vtx >> newColor;

            if (color[vtx] == newColor) {
                cout << total << '\n';
                continue;
            }

            for (int edgeID : incident[vtx]) {
                Edge &e = edges[edgeID];

                int other = (e.u == vtx) ? e.v : e.u;

                long long oldCost = e.cost;
                long long newCost = (color[other] == newColor) ? 0 : e.c;

                e.cost = newCost;
                total += newCost - oldCost;
            }

            color[vtx] = newColor;
            cout << total << '\n';
        }
    }

    return 0;
}
