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
#define prDouble(x) fixed<<setprecision(10)<<x
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (ll)(x).size()
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

ld comb(ll k){
    return (k*(k-1))/2;
}

ld pMove(ll prev, ll j, vector<vector<ld>>& p){
    ll k = __builtin_popcount(prev);
    ll den = (k*(k-1))/2;
    double ans = 0;
    for(ll fish=0;fish<n;fish++){
        if((1<<fish)&prev){
            ans += p[fish][j];
        }
    }
    return ans/(1.0*den);

}

ld Ans(vector<ld>& dp, int i, vector<vector<ld>>& p){
    ll alive = __builtin_popcount(i);
    if(alive==n) return 1;

    if(dp[i]>-0.9) return dp[i];
    ld ans = 0;
    for(ll j=0;j<n;j++){
        if((i&(1<<j))==0){
            ld prev_day = Ans(dp,i^(1<<j),p);
            ans += prev_day * pMove(i^(1<<j),j,p);
        }
    }
    return dp[i]=ans;
}

void solve() {
    cin>>n;
    vector<vector<ld>> p(n, vector<ld> (n,0));
    for(ll i=0;i<n;i++){
        read(p[i]);
    }
    vector<ld> dp(3*1e5,-1.0);
    for(ll i=0;i<n;i++){
        cout<<prDouble(Ans(dp,1<<i,p))<<" ";
    }
}

int main() {
    fastio();
    // cin >> t;
    while (t--) solve();
    return 0;
}