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
const ll INF = 1e18, MOD = 1e9+7;

ll Ans(vector<ll>& dp, ll k,const vector<ll>& h){
    if (k < 2) return 0; // base case, k out of bounds
    if (dp[k] != -1) return dp[k];

    ll sk = min(k - 2, h[k + 1] - 2);
    sk = max(0LL,sk);
    if (k == 2) {
        dp[k] = sk;
    } else {
        dp[k] = max(Ans(dp,k - 1,h), Ans(dp,k - 2,h) + sk);
    }
    return dp[k];
}


void solve() {
    cin>>n;
    vector<ll> h(n);
    read(h);

    ll sum = accumulate(all(h),0);

    ll b = sum - (n-1);
    if(n<=2){
        cout<<b<<endl;
        return;
    }
    vector<ll> dp(n+1,-1);
    ll res = Ans(dp,n-1,h);
    cout<< b - res<<endl;
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}