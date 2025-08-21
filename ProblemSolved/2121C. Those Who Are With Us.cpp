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

void solve() {
    cin>>n>>m;
    vector<int> mat(n, vector<int>(m));
    int maxi = 0, maxi_i = -1, maxi_j=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mat[i][j];
            if(mat[i][j] > maxi){
                maxi_i = i;
                maxi_j = j;
                maxi = mat[i][j];
            }
        }
    }
    ll ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==maxi_i or j==maxi_j) ans = max(ans,mat[i][j]-1);
            else ans = max(ans,mat[i][j]);
        }
    }
    cout<<ans<<endl;

}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}