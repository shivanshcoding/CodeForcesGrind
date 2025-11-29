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

const ll INF = 1e18, MOD = 1e9+7;

struct Query {
    int r, c;
    ll dec;
};

class Grid {
public:
    Grid(int rows = 0, int cols = 0)
        : n(rows), m(cols), val(rows, vector<ll>(cols)) {}

    void readValues() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> val[i][j];
    }

    void applyDecrease(int r, int c, ll x) {
        val[r][c] -= x;
    }

    int computeBeauty() const {
        vector<vector<char>> vis(n, vector<char>(m, 0));
        int res = 0;
        static const array<int,4> dx = {1,-1,0,0};
        static const array<int,4> dy = {0,0,1,-1};
        queue<pll> q;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j]) continue;
                vis[i][j] = 1;
                q.emplace(i, j);
                ll base = val[i][j];
                bool bad = false;

                while (!q.empty()) {
                    auto [x,y] = q.front();
                    q.pop();
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

                        if (val[nx][ny] == base) {
                            if (!vis[nx][ny]) {
                                vis[nx][ny] = 1;
                                q.emplace(nx, ny);
                            }
                        } else if (val[nx][ny] < base) {
                            bad = true;
                        }
                    }
                }
                if (!bad) ++res;
            }
        }
        return res;
    }

private:
    int n, m;
    vector<vector<ll>> val;
};

class Solver {
public:
    void run() {
        fastio();
        int T; 
        cin >> T;
        while (T--) solveCase();
    }

private:
    void solveCase() {
        int n, m;
        cin >> n >> m;
        Grid g(n, m);
        g.readValues();

        int qn;
        cin >> qn;
        vector<Query> qs(qn);
        for (auto &qq : qs) {
            cin >> qq.r >> qq.c >> qq.dec;
            --qq.r; 
            --qq.c;
        }

        cout << g.computeBeauty() << '\n';
        for (auto &qq : qs) {
            g.applyDecrease(qq.r, qq.c, qq.dec);
            cout << g.computeBeauty() << '\n';
        }
    }
};

int main() {
    Solver s;
    s.run();
    return 0;
}
