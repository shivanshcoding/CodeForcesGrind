#include <bits/stdc++.h>

using namespace std;

/** * Macros for convenience
 */
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define nl '\n'
#define mt make_tuple
#define mh make_heap()
#define ph push_heap()
#define pph pop_heap()

#define pqa priority_queue<ll, vector<ll>, greater<ll>>
#define vvl vector<vector<ll>>
#define vl vector<ll>
#define vs vector<string>
#define forn(i, b) for (ll i = 0; i < b; i++)
#define umap(t1, t2) unordered_map<t1, t2>

#define pl pair<ll, ll>
#define vpl vector<pair<ll, ll>>
/**
 * Common Constants
 */
const ll MOD = 1e9 + 7;    // Standard prime for modulo arithmetic
const ll MOD2 = 998244353; // Prime often used in NTT (Number Theoretic Transform)
const ll INF = 1e18;       // Infinity for ll (Dijkstra/DP)
const ll IINF = 1e9 + 7;   // Infinity for int
const ld PI = acos(-1.0);  // High-precision PI
const ld EPS = 1e-9;
const int maxarr = 5e3 + 5;
const int maxr = 1e5 + 10;
const ll N = 2e5 + 5;
const string yes = "YES";
const string no = "NO";
static string ans = yes;

const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Small epsilon for floating point comparisons

/**
 * Fast I/O Setup
 * Sync_with_stdio(0) makes cin/cout as fast as scanf/printf.
 * cin.tie(0) prevents unnecessary flushing.
 */
void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
/*vector<int> ans;
void maxy(vector<int> v,int i,int j,int n) {
   if(i>j)return;
   int max = 0;
   int ind=-1;
   for (int k=i; k<=j; k++) {
       if (v[k]>max) {
           max = v[k];
           ind = k;
       }
   }
   ans[ind]=n;
   n++;
   maxy(v,ind+1,j,n);
   maxy(v,i,ind-1,n);

}*/

bool good[maxarr][maxarr], good2[maxarr][maxarr];
int dp[maxarr];

unsigned ll power_mod(unsigned ll base, unsigned ll exp, unsigned ll mod)
{
    unsigned ll result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = ((__uint128_t)(result)*base) % mod;
        }
        base = ((__uint128_t)(base)*base) % mod;
        exp /= 2;
    }
    return result;
}

// Deterministic Miller-Rabin Primality Test for 64-bit integers
bool is_prime(unsigned ll n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 or n % 3 == 0)
        return false;

    unsigned ll d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    unsigned ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (unsigned ll a : bases)
    {
        if (n <= a)
            break;

        unsigned ll x = power_mod(a, d, n);
        if (x == 1 || x == n - 1)
            continue;

        bool composite = true;
        for (int r = 1; r < s; r++)
        {
            x = ((__uint128_t)(x)*x) % n;
            if (x == n - 1)
            {
                composite = false;
                break;
            }
        }
        if (composite)
            return false;
    }
    return true;
}

vector<bool> sieve(ll n)
{
    vector<bool> sieve(n + 1, true);
    sieve[0] = sieve[1] = false;
    for (ll i = 2; i * i <= n; i++)
    {
        if (sieve[i])
        {
            for (ll j = i * i; j <= n; j += i)
            {
                sieve[j] = false;
            }
        }
    }
    return sieve;
}
vl linear_sieve(ll n)
{
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    vl primes;
    for (ll i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            primes.pb(i);
        }
        for (ll p : primes)
        {
            if (i * p > n)
            {
                break;
            }
            is_prime[i * p] = false;
            if (i % p == 0)
            {
                break;
            }
        }
    }
    return primes;
}
set<ll> PrimeFactorization(ll n)
{
    set<ll> primeFact;
    for (ll i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            primeFact.insert(i);
            n /= i;
        }
    }
    if (n > 1)
        primeFact.insert(n);
    return primeFact;
}

// Returns ONLY the largest prime strictly smaller than n
unsigned ll get_previous_prime(unsigned ll n)
{
    if (n <= 2)
        return 0; // No primes exist strictly below 2
    if (n == 3)
        return 2; // Edge case to handle the only even prime smoothly

    // Force start at the first odd number strictly less than n
    unsigned ll current = (n % 2 == 0) ? n - 1 : n - 2;

    while (current > 2)
    {
        if (is_prime(current))
            return current;
        current -= 2; // Skip even numbers
    }
    return 2;
}

/**
 * Solve function for a single test case
 */

bool canFit(ll i, ll j, ll n, ll m)
{
    return (i >= 1 && j >= 1 && i <= n && j <= m);
}

class cmp
{
public:
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return a.first < b.first;
    }
};

ll sumr(ll n)
{
    return n * (n + 1) / 2;
}

ll sumr(ll l, ll r)
{
    return sumr(r) - sumr(l - 1);
}

ll can(string s, ll m, ll k)
{
    vl v(m + 1);
    for (ll i = m - 1; i >= 0; i--)
    {
        ll c = s[i] - '0';
        if ((c + v[0]) % 104 != 0)
        {
            ll part = 10 - (c + v[0]) % 10;
            v[0] += part;
        }
    }
    return v[0] <= k;
}

vl powersOfTwo()
{
    vl ans;
    for (ll i = 1; i <= 52; i++)
    {
        ans.pb((ll)pow(2, i));
    }
    return ans;
}

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a * b / gcd(a, b);
}

ll quick_pow(ll a, ll b, ll p)
{
    ll c = 1;
    for (; b; b >>= 1)
    {
        if (b & 1)
        {
            c = c * a;
            if (c >= p)
                c = c % p + p;
        }
        a = a * a;
        if (a >= p)
            a = a % p + p;
    }
    return c;
}
set<ll> divisors(ll g)
{
    set<ll> divs;

    for (ll i = 1; i * i <= g; i++)
    {
        if (g % i == 0)
        {
            divs.insert(i);
            if (i != g / i)
                divs.insert(g / i);
        }
    }
    return divs;
}

typedef struct
{
    ll node,
        parent,
        evenFlip,
        oddFlip,
        depth;
} cuble;
vector<pair<ll, ll>> adj[N]; // {neighbor, weight}
bool vis[N];
vl dist;
vector<pair<ll, ll>> edges;
///////////////////////////// Dijkstra //////////////////////////////
//
// void dijkstra(int src,ll n) {
//
//     fill(dist, dist + n, INF);
//
//     priority_queue<
//         pair<ll,int>,
//         vector<pair<ll,int>>,
//         greater<pair<ll,int>>
//     > pq;
//
//     dist[src] = 0;
//     pq.push({0, src});
//
//     while (!pq.empty()) {
//
//         auto [d, u] = pq.top();
//         pq.pop();
//
//         if (d != dist[u]) continue;
//
//         for (auto [v, w] : adj[u]) {
//
//             if (dist[v] > dist[u] + w) {
//
//                 dist[v] = dist[u] + w;
//                 pq.push({dist[v], v});
//             }
//         }
//     }
// }

void dijkstra(int src, ll n)
{

    // fill(dist, dist + n, INF);

    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>>
        pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {

        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto [v, w] : adj[u])
        {

            if (dist[v] > dist[u] + w)
            {

                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

//////////////////////////////// DFS ////////////////////////////////
vl lcms;
vl sizes;
void dfs(ll u)
{
    vis[u] = true;

    for (auto [v, w] : adj[u])
    {
        if (!vis[v])
        {
            dfs(v);
            lcms[u] = lcm(lcms[u], lcms[v]);
        }
    }
}
void dfssize(ll u)
{
    vis[u] = true;

    for (auto [v, w] : adj[u])
    {
        if (!vis[v])
        {
            dfssize(v);
            sizes[u] += sizes[v];
        }
    }
}

//////////////////////////////// BFS ////////////////////////////////

ll lim;

ll bfs(ll n, vl v)
{
    fill(vis, vis + N, false);

    queue<ll> q;
    q.push(n);

    while (!q.empty())
    {
        ll node = q.front();
        q.pop();
        vis[node] = true;

        if (lcms[node] != -1)
            continue;

        for (auto next : adj[node])
        {
            if (!vis[next.first])
            {
                lcms[node] = lcm(bfs(next.first, v), lcms[node]);
                vis[next.first] = true;
            }
        }
    }
}

void solve()
{
    ll n, x;
    cin >> n >> x;
    vvl v(n, vl(3));
    ll start = 0, mx = INT64_MIN;
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
        mx = max(mx, v[i][0] * v[i][1] - v[i][2]);
        start += v[i][0] * (v[i][1] - 1);
    }
    x -= start;
    if (x <= 0)
    {
        cout << 0 << nl;
        return;
    }
    if (mx <= 0)
    {
        cout << -1 << nl;
        return;
    }
    cout << (x + mx - 1) / mx << nl;
}

int main()
{
    fast_io();
    ll t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}