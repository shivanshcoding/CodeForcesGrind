#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>
#include <functional> // For std::function

using namespace std;

// Solves a single test case
void solve(int case_num) {
    int n, m;
    cin >> n >> m;

    vector<multiset<pair<int, int>>> adj(n + 1);
    vector<pair<int, int>> edges(m);
    vector<int> degree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        adj[u].insert({v, i});
        adj[v].insert({u, i});
        degree[u]++;
        degree[v]++;
    }

    vector<char> assignment(m, '0');
    vector<bool> visited_node(n + 1, false);

    for (int i = 1; i <= n; ++i) {
        if (visited_node[i] || adj[i].empty()) {
            continue;
        }

        // --- 1. Find component and odd-degree nodes (using a standard BFS) ---
        vector<int> component_nodes;
        vector<int> odd_nodes;
        vector<int> q;
        q.push_back(i);
        visited_node[i] = true;
        
        int head = 0;
        while(head < q.size()){
            int u = q[head++];
            component_nodes.push_back(u);
            if (degree[u] % 2 != 0) {
                odd_nodes.push_back(u);
            }
            // Use original degree list to find neighbors to build component
            for (auto const& p : adj[u]) {
                int neighbor = p.first;
                if (!visited_node[neighbor]) {
                    visited_node[neighbor] = true;
                    q.push_back(neighbor);
                }
            }
        }

        // --- 2. Add virtual edges ---
        for (size_t j = 0; j < odd_nodes.size(); j += 2) {
            int u = odd_nodes[j];
            int v = odd_nodes[j + 1];
            adj[u].insert({v, -1}); // -1 for virtual edge
            adj[v].insert({u, -1});
        }

        // --- 3. Find Eulerian path and store edge indices directly (Revised) ---
        vector<int> tour_edges;
        function<void(int)> find_tour = 
            [&](int u) {
            while (!adj[u].empty()) {
                auto [v, edge_idx] = *adj[u].begin();
                adj[u].erase(adj[u].begin());
                adj[v].erase(adj[v].find({u, edge_idx}));
                find_tour(v);
                tour_edges.push_back(edge_idx);
            }
        };

        find_tour(i);
        reverse(tour_edges.begin(), tour_edges.end());

        // --- 4. Assign days by alternating along the edge tour ---
        bool is_day1 = true;
        for (int edge_idx : tour_edges) {
            if (edge_idx != -1) { // Ignore virtual edges
                assignment[edge_idx] = is_day1 ? '1' : '2';
                is_day1 = !is_day1;
            }
        }
    }

    // --- 5. Calculate final cost ---
    vector<int> day1_deg(n + 1, 0);
    vector<int> day2_deg(n + 1, 0);
    long long total_cost = 0;

    for (int i = 0; i < m; ++i) {
        auto [u, v] = edges[i];
        if (assignment[i] == '1') {
            day1_deg[u]++;
            day1_deg[v]++;
        } else { // Handles unassigned ('0') or '2'
            day2_deg[u]++;
            day2_deg[v]++;
        }
    }

    for (int i = 1; i <= n; ++i) {
        total_cost += (long long)day1_deg[i] * day1_deg[i];
        total_cost += (long long)day2_deg[i] * day2_deg[i];
    }
    
    // --- 6. Print result ---
    cout << "Case #" << case_num << ": " << total_cost << " ";
    for (int i = 0; i < m; ++i) {
        cout << (assignment[i] == '0' ? '1' : assignment[i]);
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}