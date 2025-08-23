#include <bits/stdc++.h>
using namespace std;
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
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,k,a,b,q,x,y,z, MOD = 1e9+7;
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

// comparator for sorting tuples
bool comp(const tll &a, const tll &b) {
    if (get<0>(a) != get<0>(b))
        return get<0>(a) > get<0>(b); // prioritize higher audio_count
    if (get<1>(a) != get<1>(b))
        return get<1>(a) > get<1>(b); // then higher subtitle_count
    return get<2>(a) < get<2>(b);     // finally smaller movie index
}

void solve() {
    cin >> n;
    vector<ll> a(n);
    read(a);
    cin >> m;
    vector<ll> b(m), c(m);
    read(b);
    read(c);

    unordered_map<ll,ll> mpp;
    for (ll lang : a) mpp[lang]++;

    vector<tll> movies;
    for (int i = 0; i < m; i++) {
        ll t1 = mpp[b[i]]; // count of scientists knowing audio
        ll t2 = mpp[c[i]]; // count of scientists knowing subs
        movies.push_back({t1, t2, i});
    }

    sort(all(movies), comp);

    cout << get<2>(movies[0]) + 1 << "\n";
}

int main() {
    fastio();
    // cin >> t;
    while (t--) solve();
    return 0;
}
