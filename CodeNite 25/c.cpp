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

struct XORSpace {
    vector<int> base;
    int highest_bit;

    XORSpace() : highest_bit(0) {}

    void add(int x) {
        for (int b : base) x = min(x, x ^ b);
        if (x) {
            base.push_back(x);
            sort(base.rbegin(), base.rend());
        }
    }

    int rank() const {
        return (int)base.size();
    }
};

void solve() {
    cin >> n;
    vector<int> arr(n), pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        pref[i + 1] = pref[i] ^ arr[i];
    }

    if (n == 2) {
        int x = pref[1], y = pref[2];
        if (x <= (x ^ y)) {
            cout << x << " " << (x ^ y) << '\n';
            return;
        }
        if (y <= (y ^ x)) {
            cout << y << " " << (y ^ x) << '\n';
            return;
        }
        cout << -1 << '\n';
        return;
    }

    XORSpace space;
    for (int i = 1; i <= n; ++i) space.add(pref[i]);

    int k = space.rank();
    if (n < k) {
        cout << -1 << '\n';
        return;
    }

    sort(space.base.begin(), space.base.end());
    vector<int> out(n, 0);
    for (int i = 0; i < k; ++i) out[n - k + i] = space.base[i];

    for (int i = 0; i < n; ++i) {
        cout << out[i] << (i + 1 == n ? '\n' : ' ');
    }
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}
