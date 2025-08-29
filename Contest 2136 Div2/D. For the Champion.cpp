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
const ll INF = 1e18, MOD = 1e9+7, LIMIT = 1e9;

static ll interact(char d, ll k) {
    cout << "? " << d << " " << k << endl << flush;
    ll r; 
    if (!(cin >> r)) exit(0);
    if (r == -1) exit(0);
    return r;
}


void solve() {
    int n; 
    cin >> n;
    vector<pll> pts(n);
    for (auto &p : pts) cin >> p.first >> p.second;

    // instead of ranges::max, do normal loops
    ll mx_sum = LLONG_MIN, mx_diff = LLONG_MIN;
    for (auto &p : pts) {
        mx_sum  = max(mx_sum,  p.first + p.second);
        mx_diff = max(mx_diff, p.first - p.second);
    }

    auto run = [&](char dir, int times) {
        ll res = 0;
        for (int i = 0; i < times; i++) res = interact(dir, LIMIT);
        return res;
    };

    run('R', 2);                // right shift
    ll res_up   = run('U', 2);  // after up
    ll res_down = run('D', 4);  // after down

    ll partA = res_up   - 4LL*LIMIT + mx_sum;
    ll partB = res_down - 4LL*LIMIT + mx_diff;

    ll X = (partA + partB) / 2;
    ll Y = (partA - partB) / 2;

    cout << "! " << X << " " << Y << endl << flush;
}

int main() {
    fastio();
    int t; 
    cin >> t;
    while (t--) solve();
    return 0;
}
