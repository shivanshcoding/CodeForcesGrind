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
const ll INF = 1e18, MOD = 998244353;

ll power(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp % 2) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

ll countL(int i, int j, vector<ll>& Lh, vector<ll>& h, int maxi){
    if (i >= n || j >= (int)Lh.size()) return 0;
    if(h[i]==maxi){
        if(Lh[j]==maxi){
            return 1;
        }else{
            return 0;
        }
    }
    ll ans = 0;
    if(h[i]==Lh[j]){
        ans = (ans+countL(i+1,j+1,Lh,h,maxi))%MOD;
        ans = (ans+countL(i+1,j,Lh,h,maxi))%MOD;
    }else{
        ans = (ans+2*countL(i+1,j,Lh,h,maxi))%MOD;
    }
    return ans%MOD;
}


ll countR(int i, int j, vector<ll>& Lh, vector<ll>& h, int maxi){
    if (i < 0 || j >= (int)Lh.size()) return 0;
    if(h[i]==maxi){
        if(Lh[j]==maxi){
            return 1;
        }else{
            return 0;
        }
    }
    ll ans =  0;
    if(h[i]==Lh[j]){
        ans = (ans+countR(i-1,j+1,Lh,h,maxi))%MOD;
    }
    ans = (ans+countR(i-1,j,Lh,h,maxi))%MOD;
    return ans%MOD;
}



void solve() {
    cin>>n;
    vector<ll> h(n);
    read(h);
    vector<ll> Lh, Rh;
    int curr =0;
    int le = -1, re = n;
    for(int i=0;i<n;i++){
        if(h[i] > curr){
            Lh.pb(h[i]);
            curr = h[i];
            le = i;
        }else if(h[i]==curr){
            le = i;
        }
    }
    curr = 0;
    for(int i=n-1;i>=0;i--){
        if(h[i] > curr){
            Rh.pb(h[i]);
            curr = h[i];
            re = i;
        }else if(h[i]==curr){
            re = i;
        }
    }
    ll ans = (((countL(0,0,Lh,h,curr)*(power(2,(re-le+1))-1))%MOD)*countR(n-1,0,Rh,h,curr))%MOD;
    cout<<ans<<endl;
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}