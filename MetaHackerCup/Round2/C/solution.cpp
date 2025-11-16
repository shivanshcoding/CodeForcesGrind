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
ll T=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

//
class FastDSU {
public:
    FastDSU() {}
    FastDSU(int n) { initialize(n); }

    void initialize(int n) {
        length = n;
        parent.assign(n + 2, 0);
        for (int i = 1; i <= n + 1; ++i) parent[i] = i;
    }

    // Standard DSU path-compression find.
    int locate(int x) {
        while (x <= length + 1 && parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void deactivate(int x) {
        parent[x] = x + 1;
    }

private:
    vector<int> parent;
    int length = 0;
};

class Route {
public:
    vector<int> nodes;
};

class TransitSolver {
public:
    TransitSolver(int n, int k, int m)
        : N(n), K(k), M(m), 
          dist(n + 1, -1),
          routeList(m),
          jump(m),
          appear(n + 1) {}

    void loadRoutes() {
        for (int r = 0; r < M; ++r) {
            int len;
            cin >> len;

            routeList[r].nodes.resize(len);
            for (int j = 0; j < len; ++j) {
                cin >> routeList[r].nodes[j];
                appear[ routeList[r].nodes[j] ].push_back({r, j + 1});
            }

            jump[r].initialize(len);
        }
    }

    void runBFS() {
        deque<int> dq;
        dist[1] = 0;
        dq.push_back(1);

        while (!dq.empty()) {
            int current = dq.front();
            dq.pop_front();

            int dCur = dist[current];

            // Each time we arrive at a court, we process all its route appearances.
            for (auto &occ : appear[current]) {
                int rID  = occ.first;
                int pos  = occ.second;
                int len  = routeList[rID].nodes.size();

                // We can move forward up to K stops.
                int start = pos + 1;
                if (start > len) continue;
                int endp = min(len, pos + K);

                // Jump through unvisited positions quickly
                int idx = jump[rID].locate(start);
                while (idx <= endp) {
                    int nxtNode = routeList[rID].nodes[idx - 1];

                    // Mark the position as processed (so future occurrences skip it)
                    jump[rID].deactivate(idx);

                    // BFS relaxation step
                    if (dist[nxtNode] == -1) {
                        dist[nxtNode] = dCur + 1;
                        dq.push_back(nxtNode);
                    }

                    idx = jump[rID].locate(idx); 
                }
            }

            // Optional micro-optimization: we never need to revisit the same appearances.
            appear[current].clear();
        }
    }

    long long computeScore() const {
        long long total = 0;
        for (int i = 1; i <= N; ++i) {
            total += 1LL * i * dist[i];
        }
        return total;
    }

private:
    int N, K, M;
    vector<int> dist;
    vector<Route> routeList;
    vector<FastDSU> jump;
    vector<vector<pair<int,int>>> appear;
};


int main() {
    fastio();

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N, K, M;
        cin >> N >> K >> M;

        TransitSolver solver(N, K, M);
        solver.loadRoutes();
        solver.runBFS();
        long long answer = solver.computeScore();

        cout << "Case #" << t << ": " << answer << "\n";
    }

    return 0;
}
