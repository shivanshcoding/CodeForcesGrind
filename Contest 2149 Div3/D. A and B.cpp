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
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << "(" << x.f <<","<< x.second << ")" << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

void CountPref(vector<pll>& pref, string& s, char ch){
    pll curr = {0,-1};
    ll l = -1;
    for(int i=0;i<n;i++){
        if(s[i]==ch){
            if(curr.second==-1){
                pref[i] = {0,1};
                curr = pref[i];
                l = i;
            }else{
                ll shift = i-l-1;
                pref[i] = {curr.first + curr.second*shift, curr.second+1};
                curr = pref[i];
                l = i;
            }
        }
    }
}
void CountSuff(vector<pll>& pref, string& s, char ch){
    pll curr = {0,n};
    ll l = n;
    for(int i=n-1;i>=0;i--){
        if(s[i]==ch){
            if(curr.second==n){
                pref[i] = {0,1};
                curr = pref[i];
                l = i;
            }else{
                ll shift = l-i-1;
                pref[i] = {curr.first + curr.second*shift, curr.second+1};
                curr = pref[i];
                l = i;
            }
        }
    }
}


void solve() {
    cin>>n;
    string s;
    cin>>s;
    vector<pll> pref_b(n,{0,-1}), pref_a(n,{0,-1}), suff_b(n,{0,-1}), suff_a(n,{0,-1});
    ll ans = LLONG_MAX;
    CountPref(pref_b,s,'b');
    //printv(pref_b);
    //cout<<"\n";
    CountSuff(suff_b,s,'b');
    //printv(suff_b);
    //cout<<"\n";
    CountPref(pref_a,s,'a');
    //printv(pref_a);
    //cout<<"\n";
    CountSuff(suff_a,s,'a');
    //printv(suff_a);
    //cout<<"\n";
    for(int i=0;i<n;i++){
        if(s[i]=='a'){
            ans = min(ans,pref_a[i].f+suff_a[i].f);
        }else{
            ans = min(ans,pref_b[i].f+suff_b[i].f);
        }
    }
    cout<<ans<<"\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}