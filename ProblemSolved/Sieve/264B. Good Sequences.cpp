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

vector<vector<ll>> dp;

ll Ans(vector<ll>& a, ll i, ll p){
    if(i==n) return 0;
    if(dp[i][p+1]!=-1) return dp[i][p+1];
    ll nottake = Ans(a,i+1,p);
    ll take = 0;
    if(p==-1 or gcd(a[i],a[p])>1){
        take = 1+Ans(a,i+1,i);
    }
    return dp[i][p+1] = max(nottake,take);
}

void solve() {
    cin>>n;
    vector<ll> a(n);
    read(a);
    dp.assign(n, vector<ll> (n,-1));
    cout<<Ans(a,0,-1);

}

int main() {
    fastio();
    // cin >> t;
    while (t--) solve();
    return 0;
}