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

constexpr ll INF64 = (ll)4e18;


static inline ll required_limit(ll rem, ll K) {
    if (rem >= K) return 0;
    ll denom = rem + 1;
    ll numer = K - rem;
    return numer / denom;
}

class Matcher {
public:
    static ll match_and_count(vector<ll>& a, const vector<ll>& b, ll K) {
        int n = a.size();
        if (n == 0) return 0;

        sort(a.begin(), a.end());

        set<int> avail;
        for (int i = 0; i < n; ++i) avail.insert(i);

        vector<ll> lims;
        lims.reserve(b.size());
        for (ll rem : b) {
            if (rem >= K) continue;
            ll lim = required_limit(rem, K);
            if (lim >= 1) lims.push_back(lim);
        }

        sort(lims.begin(), lims.end());

        ll res = 0;

        for (ll lim : lims) {
            auto itPos = upper_bound(a.begin(), a.end(), lim);
            int pos = (int)distance(a.begin(), itPos); // pos in [0..n]
            auto sit = avail.lower_bound(pos);
            if (sit == avail.begin()) {
                continue;
            }
            --sit;
            avail.erase(sit);
            ++res;
            if (avail.empty()) break;
        }

        return res;
    }
};


int main() {
    fastio();

    if (!(cin >> t)) return 0;
    while (t--) {
        cin >> n >> k;
        vector<ll> a(n),b(n);
        read(a);
        read(b);
        ll ans = Matcher::match_and_count(a, b, k);
        cout << ans << '\n';
    }
    return 0;
}
