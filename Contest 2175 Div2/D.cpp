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
ll t = 1, n, m, p, q, r, k, a, b, c, x, y, z;
const ll INF = 1e18, MOD = 1e9 + 7;

struct Node
{
    int at;
    ll score;
    Node(int p = INT_MAX, ll s = (ll)-4e18) : at(p), score(s) {}
};

struct Solver
{
    int n, k;
    int w;
    vector<int> cap;
    vector<int> nxt;
    vector<Node> dp, buf;

    Solver(int n_, int k_, const vector<int> &a) : n(n_), k(k_), cap(a)
    {
        w = k + 1;
        nxt.assign((n + 2) * w, n + 1);
        dp.assign((k + 1) * (k + 1), Node());
        buf.assign((k + 1) * (k + 1), Node());
        buildNext();
    }

    int id(int cost, int lv) const
    {
        return cost * w + lv;
    }

    void buildNext()
    {
        int b = (n + 1) * w;
        for (int v = 0; v <= k; ++v)
            nxt[b + v] = n + 1;
        for (int i = n; i >= 1; --i)
        {
            int row = i * w;
            int nr = (i + 1) * w;
            for (int v = 1; v <= k; ++v)
            {
                if (cap[i] >= v)
                    nxt[row + v] = i;
                else
                    nxt[row + v] = nxt[nr + v];
            }
        }
    }

    void clearBuf()
    {
        int sz = (k + 1) * (k + 1);
        for (int i = 0; i < sz; ++i)
            buf[i] = Node();
    }

    ll run()
    {
        dp[id(0, 0)] = Node(0, 0);
        vector<int> fr;
        fr.push_back(id(0, 0));
        ll best = 0;

        int ls = 0;
        while ((ll)(ls + 1) * (ls + 2) / 2 <= k)
            ++ls;
        if (ls == 0)
            ls = 1;

        for (int step = 1; step <= ls; ++step)
        {
            clearBuf();
            vector<int> nextfr;
            vector<char> vis((k + 1) * (k + 1), 0);

            for (int code : fr)
            {
                int cost = code / w;
                int lv = code % w;
                Node cur = dp[code];
                if (cur.at == INT_MAX)
                    continue;

                for (int nv = lv + 1; cost + nv <= k; ++nv)
                {
                    int nc = cost + nv;
                    int start = cur.at + 1;
                    if (start > n)
                        continue;

                    int who = nxt[start * w + nv];
                    if (who > n)
                        continue;

                    ll gain = (ll)(nv - lv) * (n - who + 1);
                    ll cand = cur.score + gain;

                    int to = id(nc, nv);
                    Node &dst = buf[to];

                    bool flag = false;
                    if (dst.at == INT_MAX)
                    {
                        dst.at = who;
                        dst.score = cand;
                        flag = true;
                    }
                    else if (who < dst.at)
                    {
                        dst.at = who;
                        dst.score = cand;
                        flag = true;
                    }
                    else if (who == dst.at && cand > dst.score)
                    {
                        dst.score = cand;
                        flag = true;
                    }

                    if (flag)
                    {
                        best = max(best, cand);
                        if (!vis[to])
                        {
                            vis[to] = 1;
                            nextfr.push_back(to);
                        }
                    }
                }
            }

            if (nextfr.empty())
                break;
            dp.swap(buf);
            fr.swap(nextfr);
        }

        return best;
    }
};

int main()
{
    fastio();
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        Solver solver(n, k, a);
        ll res = solver.run();
        cout << res << '\n';
    }
    return 0;
}
