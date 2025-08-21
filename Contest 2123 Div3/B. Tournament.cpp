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
ll t=1,n,m,k,a,b,q,x,y,z,i,j, MOD = 1e9+7;
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


int bs(vector<ll>& a, ll val){
    int s = 0;
    int e = a.size()-1;
    int ans = e;
    while(s<=e){
        int mid = s+((e-s)/2);
        if(a[mid]>=val){
            ans = min(ans,mid);
            e = mid-1;
        }else{
            s = mid+1;
        }
    
    }
    return ans;
}

void solve() {
    cin>>n>>j>>k;
    vector<ll> a(n);
    read(a);
    ll val = a[j-1];
    bool found = false;
    for(ll i: a){
        if(i>val){
            found = true;
            break;
        }
    }
    if(found){
        if(k==1) {
            cout<<"NO";
            return;
        }
    }
    cout<<"YES";
}

int main() {
    fastio();
    cin >> t;
    while (t--){
        solve();
        cout<<endl;
    }
    return 0;
}