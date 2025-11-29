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
const ll INF = 1e18, MOD = 1e9+7;

ll maxisum(vector<ll>& a){
    int r = 0;
    ll sum = 0, maxi = *min_element(a.begin(),a.end());
    if(*max_element(a.begin(),a.end())<0){
        return *max_element(a.begin(),a.end());
    }
    while(r<n){
        sum+=a[r];
        maxi = max(maxi,sum);
        if(sum<0){
            sum = 0;
        }
        r++;
    }
    return maxi;
}

ll maxisum2(vector<ll>& a, vector<ll>& b){
    ll dp0 = -1e18, dp1 = -1e18, res = -1e18;

    for(int i=0;i<n;i++) {
        ll prev_dp0 = dp0;
        ll prev_dp1 = dp1;
        ll exm = prev_dp1+a[i];
        ll crm = max(prev_dp0+a[i]+b[i],a[i]+b[i]);
        dp1 = max(exm, crm);
        dp0 = max(prev_dp0+a[i],a[i]);
        res = max(res, dp1);
    }

    return res;
}


void solve() {
    cin>>n>>k;
    vector<ll> a(n),b(n);
    read(a);
    read(b);
    bool ok = false;
    for(int i=0;i<n;i++){
        if(b[i]!=0){
            ok = true;
            break;
        }
    }
    if(!ok or k%2==0){
        cout<<maxisum(a)<<"\n";
    }else{
        cout<<maxisum2(a,b)<<"\n";
    }
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}



