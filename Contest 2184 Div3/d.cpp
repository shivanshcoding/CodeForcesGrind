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
using ld = long double;
typedef long long ll;
using pll = pair<ll,ll>;
using tll = tuple<ll,ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,x,y,z;
const ll MOD = 1e9+7;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
 
ll c[2010][2010];
 
void init() {
    for (int i = 0; i < 2010; i ++ ) {
        for (int j = 0; j <= i; j ++ ) {
            if (j == 0) c[i][j] = 1;
            else c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
}
 
void solve() {
    ll n, k;
    cin >> n >> k;
 
    int pos = 0;
    for (int i = 32; i >= 0; i -- ) {
        if (((ll)1 << i) & n) {
            pos = i;
            break;
        }
    }
 
    ll ans = 0;
    for (int i = pos; i >= 1; i -- ) {
        for (int j = i - 1; j >= 0; j -- ) {
            if (i + j > k) ans += c[i - 1][j];
        }
    }
 
    if (pos + 1 > k) ans ++ ;
 
    cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    init();
    int tt = 1;
    cin >> tt;
    while (tt -- ) solve();
 
    return 0;
}