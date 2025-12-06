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

struct ModOps
{
    ll mod;

    explicit ModOps(ll m = 1) : mod(m) {}

    ll add(ll a, ll b) const
    {
        a %= mod;
        b %= mod;
        ll res = a + b;
        if (res >= mod)
            res -= mod;
        return res;
    }

    ll sub(ll a, ll b) const
    {
        a %= mod;
        b %= mod;
        ll res = a - b;
        if (res < 0)
            res += mod;
        return res;
    }

    ll mul(ll a, ll b) const
    {
        a %= mod;
        b %= mod;
        return (a * b) % mod;
    }

    ll binPow(ll base, ll exp) const
    {
        base %= mod;
        ll res = 1;
        while (exp > 0)
        {
            if (exp & 1)
                res = mul(res, base);
            base = mul(base, base);
            exp >>= 1;
        }
        return res;
    }

    // Fermat inverse -> mod must be prime
    ll inv(ll x) const
    {
        return binPow(x, mod - 2);
    }
};

struct IntervalProbabilitySolver
{
    int n;
    ll m;
    ll P;
    ModOps op;
    vector<ll> pq;

    IntervalProbabilitySolver(int n_, ll m_, ll mod_)
        : n(n_), m(m_), P(mod_), op(mod_)
    {
        ppp();
    }

    void ppp()
    {
        ll q = op.inv(m);
        pq.assign(n + 1, 0);
        pq[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            pq[i] = op.mul(pq[i - 1], q);
        }
    }

    ll solve()
    {
        ll tps = 0, tc = 0;

        for (int S = 2; S <= 2 * n; S++)
        {
            int leftMin = max(1, S - n);
            int leftMax = S / 2;

            if (leftMin > leftMax)
                continue;

            int ci = leftMax - leftMin + 1;

            ll lps = 0, wp = 0;

            int startExp = (S % 2 == 0 ? 0 : 1);

            for (int j = 1; j <= ci; ++j)
            {
                int exponent = startExp + (j - 1);
                ll prob = pq[exponent];

                lps = op.add(lps, prob);

                ll weight = (2LL * j - 1) % P;
                ll term = op.mul(weight, prob);
                wp = op.add(wp, term);
            }

            ll term1 = wp, term2 = op.mul(lps, lps);

            ll cc = op.sub(term1, term2);

            tc = op.add(tc, cc);
            tps = op.add(tps, lps);
        }
        ll ans = op.mul(tps, tps);
        ans = op.add(ans, tc);
        return ans;
    }
};

int main()
{
    fastio();
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> p;

        IntervalProbabilitySolver solver(n, m, p);
        ll res = solver.solve();
        cout << res << '\n';
    }

    return 0;
}
