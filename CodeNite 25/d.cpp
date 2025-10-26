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

static constexpr ll MODULO = 1'000'000'007LL;

struct Transform
{
    ll A; // multiplicative factor
    ll B; // additive factor
    Transform(ll a = 1, ll b = 0) : A(a % MODULO), B(b % MODULO) {}
};

// --- Modular arithmetic helpers ---
inline ll modAdd(ll x, ll y)
{
    ll z = x + y;
    if (z >= MODULO)
        z -= MODULO;
    return z;
}
inline ll modSub(ll x, ll y)
{
    ll z = x - y;
    if (z < 0)
        z += MODULO;
    return z;
}
inline ll modMul(ll x, ll y)
{
    return (x % MODULO) * (y % MODULO) % MODULO;
}
ll modPow(ll base, ll exp)
{
    ll res = 1 % MODULO;
    base %= MODULO;
    while (exp > 0)
    {
        if (exp & 1)
            res = modMul(res, base);
        base = modMul(base, base);
        exp >>= 1;
    }
    return res;
}
inline ll modInv(ll x)
{
    // MODULO is prime, use Fermat's little theorem
    return modPow((x % MODULO + MODULO) % MODULO, MODULO - 2);
}

// --- Engine encapsulates parameters and the segment tree ---
class CascadeEngine
{
    int n;                       // number of stages
    vector<array<ll, 4>> params; // u, v, m, s per stage
    vector<Transform> seg;       // segment tree
    Transform identity = Transform(1, 0);

    // Combine two sequential transforms: right ∘ left
    static Transform combineTransforms(const Transform &left, const Transform &right)
    {
        // If left: E_mid = left.A * E_in + left.B
        // and right: E_out = right.A * E_mid + right.B
        // combined: E_out = (right.A * left.A) * E_in + (right.A * left.B + right.B)
        ll newA = modMul(right.A, left.A);
        ll newB = modAdd(modMul(right.A, left.B), right.B);
        return Transform(newA, newB);
    }

    // Build transform for one stage index
    Transform makeTransformAt(int idx) const
    {
        // params[idx] = {u, v, m, s}
        ll u = params[idx][0];
        ll v = params[idx][1];
        ll m = params[idx][2];
        ll s = params[idx][3];

        ll p = modMul(u, modInv(v));            // p = u/v mod
        ll one_minus_p = modSub(1, p);          // (1 - p)
        ll m_minus_1 = modSub(m % MODULO, 1);   // (m - 1) mod
        ll A = modAdd(modMul(p, m_minus_1), 1); // A = p*(m-1) + 1
        ll B = modMul(one_minus_p, s % MODULO); // B = (1-p) * s
        return Transform(A, B);
    }

    void buildTree(int node, int l, int r)
    {
        if (l == r)
        {
            seg[node] = makeTransformAt(l);
            return;
        }
        int mid = (l + r) >> 1;
        buildTree(node << 1, l, mid);
        buildTree(node << 1 | 1, mid + 1, r);
        seg[node] = combineTransforms(seg[node << 1], seg[node << 1 | 1]);
    }

    void updateTree(int node, int l, int r, int pos)
    {
        if (l == r)
        {
            seg[node] = makeTransformAt(pos);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            updateTree(node << 1, l, mid, pos);
        else
            updateTree(node << 1 | 1, mid + 1, r, pos);
        seg[node] = combineTransforms(seg[node << 1], seg[node << 1 | 1]);
    }

    // Query combined transform on [ql, qr]
    Transform queryTree(int node, int l, int r, int ql, int qr) const
    {
        if (ql > qr)
            return identity;
        if (l == ql && r == qr)
            return seg[node];
        int mid = (l + r) >> 1;
        Transform leftRes = queryTree(node << 1, l, mid, ql, min(qr, mid));
        Transform rightRes = queryTree(node << 1 | 1, mid + 1, r, max(ql, mid + 1), qr);
        return combineTransforms(leftRes, rightRes);
    }

public:
    CascadeEngine() : n(0) {}

    // Initialize with N stages and the parameter tuples
    void initialize(int N, const vector<array<ll, 4>> &initial)
    {
        n = N;
        params = initial;
        seg.assign(4 * max(1, n), identity);
        if (n > 0)
            buildTree(1, 0, n - 1);
    }

    // Reconfigure a single stage at index pos with new params
    void reconfigure(int pos, ll u, ll v, ll m, ll s)
    {
        params[pos][0] = u;
        params[pos][1] = v;
        params[pos][2] = m;
        params[pos][3] = s;
        if (n > 0)
            updateTree(1, 0, n - 1, pos);
    }

    // Run the pipeline from L..R starting from x0
    ll runRange(int L, int R, ll x0) const
    {
        if (L > R)
            return x0 % MODULO;
        Transform combined = queryTree(1, 0, n - 1, L, R);
        ll res = modAdd(modMul(combined.A, x0 % MODULO), combined.B);
        return res;
    }
};

void solve()
{
    cin >> n >> q;

    vector<array<ll, 4>> initial(n);
    for (int i = 0; i < n; ++i)
    {
        ll u, v, m, s;
        cin >> u >> v >> m >> s;
        initial[i] = {u, v, m, s};
    }

    CascadeEngine engine;
    engine.initialize(n, initial);

    for (int qi = 0; qi < q; ++qi)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int idx;
            ll u, v, m, s;
            cin >> idx >> u >> v >> m >> s;
            engine.reconfigure(idx, u, v, m, s);
        }
        else
        {
            int L, R;
            ll x0;
            cin >> L >> R >> x0;
            cout << engine.runRange(L, R, x0) << '\n';
        }
    }
}

int main()
{
    fastio();

    if (!(cin >> t))
        return 0;
    while (t--)
    {
        solve();
    }

    return 0;
}
