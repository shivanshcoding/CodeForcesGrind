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
ll t=1,n,h,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

void solve() {
    cin>>n>>h;
    vector<ll> a(n);
    read(a);

    vector<vector<ll>> cost(n, vector<ll>(n, 0));
    for (int i=0; i<n;i++) {
        ll maxi = a[i];
        for (int j=i;j<n;j++) {
            maxi = max(maxi, a[j]);
            cost[i][j] = cost[j][i] = max(0LL, h - maxi);
        }
    }
    vector<ll> val_suff(n, 0);
    vector<ll> best_suff(n+2, 0);
    for (int k =n-1; k>=0;k--) {
        ll max_val = 0;
        for (int x_d = 0; x_d < n; x_d++) {
            val_suff[x_d] += cost[x_d][k];
            if (x_d >= k) {
                max_val = max(max_val, val_suff[x_d]);
            }
        }
        best_suff[k + 1] = max_val;
    }

    vector<ll> val_pref(n, 0);
    vector<ll> best_pref(n + 1, 0);
    for (int k = 0;k<n;k++) {
        ll max_val = 0;
        for (int x_d =0; x_d<n;x_d++) {
            val_pref[x_d]+=cost[x_d][k];
            if (x_d<=k) {
                max_val =max(max_val,val_pref[x_d]);
            }
        }
        best_pref[k + 1] =max_val; 
    }

    ll ans=0;
    for (int k=0;k<=n;k++) {
        ans = max(ans,best_pref[k]+best_suff[k + 1]);
    }

    cout<<ans<<"\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}