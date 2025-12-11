#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#define prDouble(x) cout << fixed << setprecision(10) << x
#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};                               // for grid
vector<ll> ddx = {1, 1, 0, -1, -1, -1, 0, 1}, ddy = {0, 1, 1, 1, 0, -1, -1, -1}; // 8 directions
template <typename T>
void read(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}
template <typename T>
void printv(const vector<T> &v)
{
    for (auto &x : v)
        cout << x << ' ';
}
template <typename T>
void print2d(const vector<vector<T>> &v)
{
    for (auto &row : v)
    {
        for (auto &x : row)
            cout << x << ' ';
        cout << '\n';
    }
}
const ll MOD = 998244353;

struct Edge
{
    int from;
    int to;
    ll weight;
};

class FibonacciPaths
{
public:
    void runCase()
    {
        int n, m;
        if (!(cin >> n >> m))
            return;

        vector<ll> val(n);
        for (int i = 0; i < n; ++i)
            cin >> val[i];

        vector<Edge> edges;
        edges.reserve(m);
        int cnt = m;
        while (cnt-- > 0)
        {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            edges.push_back({u, v, val[u] + val[v]});
        }

        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
             { return a.weight > b.weight; });

        vector<map<ll, ll>> dp(n);
        ll total = 0;

        for (auto &edge : edges)
        {
            ll need = edge.weight;
            ll ext = 0;
            auto it = dp[edge.to].find(need);
            if (it != dp[edge.to].end())
                ext = it->second;

            ll cur = (1 + ext) % MOD;
            dp[edge.from][val[edge.to]] = (dp[edge.from][val[edge.to]] + cur) % MOD;
            total = (total + cur) % MOD;
        }

        cout << total << '\n';
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;
    FibonacciPaths solver;
    while (T--)
        solver.runCase();
    return 0;
}
