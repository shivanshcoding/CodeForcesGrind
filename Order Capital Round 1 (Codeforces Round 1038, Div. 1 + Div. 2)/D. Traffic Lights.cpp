#include <bits/stdc++.h>
using namespace std;
#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
// using mint = modint1000000007;
// using mint = double;
#endif
 
//define
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<long long , long long>;
using vi = vector<int>;
using vll = vector<long long>;
 
#define rep(i,l,r) for (int i = (int)(l); i < (int)(r); i++)
#define rrep(i,l,r) for (int i = (int)(r-1); i >= (int)(l); i--)
#define len(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define elif else if
#define endl "\n"
const int inf = 1e9;
const long long infl = 1LL<<60;
const int mod = 998244353;
ll pow(ll a, ll b, ll p){ ll ans = 1; while(b){ if(b & 1) (ans *= a) %= p; (a *= a) %= p; b /= 2; } return ans; }
template<class T, class U> bool chmin(T& a, const U& b){ if(a > T(b)){ a = b; return 1; } return 0; }
template<class T, class U> bool chmax(T& a, const U& b){ if(a < T(b)){ a = b; return 1; } return 0; }
template <class T>
using spq = priority_queue<T, vector<T>, greater<T>>;
 
template<class T>istream& operator>>(istream& i, vector<T>& v) {for(int j = 0; j < (int)(v).size(); j++) i >> v[j]; return i;}
struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(15);
        cerr << fixed << setprecision(15);
    }
} iosetup;
 
void solve(){
    int n, m; cin >> n >> m;
    vector<vi> e(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    vi dp(n, inf);
    dp[0] = 0;
    int t = 0;
    while (true){
        vi ndp(n, inf);
        rep(i, 0, n){
            if (dp[i] != inf){
                chmin(ndp[i], dp[i]+1);
                chmin(ndp[e[i][t%len(e[i])]], dp[i]);
            }
        }
        swap(dp, ndp);
        t++;
        if (dp[n-1] != inf){
            cout << t << " " << dp[n-1] << endl;
            return ;
        }
    }
}
 
int main(){
    int t; cin >> t;
    while(t--) solve();
    return 0;
}