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
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2)); 
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

void solve() {
    cin>>n;
    vector<vector<ll>> grid(2, vector<ll> (n));
    for(int i=0;i<2;i++){
        for(int j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    vector<pll> suff(n);
    ll currmaxi = 0, currmini = INF;
    for(int i=n-1;i>=0;i--){
        currmaxi = max(currmaxi,grid[1][i]);
        currmini = min(currmini,grid[1][i]);
        suff[i].f = currmaxi;
        suff[i].s = currmini;
    }
    
    vpll pairs;
    currmaxi = 0, currmini = INF;
    for(int i=0;i<n;i++){
        currmaxi = max(currmaxi,grid[0][i]);
        currmini = min(currmini,grid[0][i]);
        pairs.push_back({min(currmini,suff[i].s), max(currmaxi,suff[i].f)});
    }

    sort(all(pairs));
    vpll minimal_pairs;
    ll min_R_so_far = INF;

    for(int i = pairs.size() - 1; i >= 0; i--) {
        if (pairs[i].s < min_R_so_far) {
            if (minimal_pairs.empty() || pairs[i].f < minimal_pairs.back().f) {
                minimal_pairs.push_back(pairs[i]);
            }
            min_R_so_far = pairs[i].s;
        }
    }

    if (minimal_pairs.empty()) {
        cout << 0 << "\n";
        return;
    }
    
    ll L_max = minimal_pairs.back().f;
    ll R_min = minimal_pairs.back().s;
    ll ans = 0;
    ll N2 = 2 * n;

    ll l1 = 1;
    ll r1 = min(L_max, R_min - 1);
    if (l1 <= r1) {
        ll count = r1 - l1 + 1;
        ll term = max(0LL, N2 - R_min + 1);
        ans += count * term;
    }

    ll l2 = max(1LL, R_min);
    ll r2 = L_max;
    if (l2 <= r2) {
        ll l2_eff = max(l2, 1LL);
        ll r2_eff = min(r2, N2);
        
        if(l2_eff <= r2_eff) {
            ll term_first = N2 - l2_eff + 1;
            ll term_last = N2 - r2_eff + 1;
            ll count = r2_eff - l2_eff + 1;
            ans += count * (term_first + term_last) / 2;
        }
    }
    
    cout << ans << "\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}