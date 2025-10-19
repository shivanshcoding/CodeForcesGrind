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

class TreeNavigator {
private:
    int n;
    vector<vector<int>> graph;
    vector<int> parent;
    vector<bool> path_marker;
    vector<int> main_path;
    vector<pair<int, int>> operations;

    bool dfsPathFinder(int node, int parent_node, int destination) {
        parent[node] = parent_node;
        if (node == destination) return true;
        for (int neighbor : graph[node]) {
            if (neighbor != parent_node) {
                if (dfsPathFinder(neighbor, node, destination))
                    return true;
            }
        }
        return false;
    }

    void buildMainPath() {
        main_path.clear();
        int current = n;
        while (current != 0) {
            main_path.push_back(current);
            path_marker[current] = true;
            current = parent[current];
        }
        reverse(main_path.begin(), main_path.end());
    }

    void pruneAndRecord() {
        vector<set<int>> tempGraph(n + 1);
        for (int i = 1; i <= n; ++i)
            for (int v : graph[i])
                tempGraph[i].insert(v);

        operations.clear();
        for (size_t i = 0; i + 1 < main_path.size(); ++i) {
            int u = main_path[i];
            int next = main_path[i + 1];

            vector<int> neighbors(tempGraph[u].begin(), tempGraph[u].end());

            for (int neighbor : neighbors) {
                if (neighbor == next) continue;

                // stabilize movement
                if (i > 0 || !operations.empty()) {
                    operations.emplace_back(1, 0);
                    operations.emplace_back(1, 0);
                }

                operations.emplace_back(2, neighbor);
                tempGraph[u].erase(neighbor);
                tempGraph[neighbor].erase(u);
            }

            operations.emplace_back(1, 0);
        }
    }

public:
    TreeNavigator(int nodes) {
        reset(nodes);
    }

    void reset(int nodes) {
        n = nodes;
        graph.assign(n + 1, {});
        parent.assign(n + 1, 0);
        path_marker.assign(n + 1, false);
        main_path.clear();
        operations.clear();
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void process() {
        dfsPathFinder(1, 0, n);
        buildMainPath();
        pruneAndRecord();
    }

    void printResults() const {
        cout << operations.size() << "\n";
        for (auto [type, val] : operations) {
            if (type == 1) cout << "1\n";
            else cout << "2 " << val << "\n";
        }
    }
};

class Solution {
public:
    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> t;
        while (t--) {
            cin >> n;
            TreeNavigator solver(n);

            for (int i = 0; i < n - 1; ++i) {
                int u, v;
                cin >> u >> v;
                solver.addEdge(u, v);
            }

            solver.process();
            solver.printResults();
        }
    }
};

int main() {
    Solution().run();
    return 0;
}
