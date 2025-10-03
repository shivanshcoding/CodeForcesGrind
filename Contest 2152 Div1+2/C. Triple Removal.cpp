#include <bits/stdc++.h>
using namespace std;
struct pair_hash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<long long>()(((long long)p.first) << 32 | p.second);
    }
};

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
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; } 
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;
void alt(vector<int> &s, vector<int>& arr) {
    int l = 0, r = 1;
    while(r<n){
        if(s[r]==s[r-1]){
            if(r-l+1 >= 6){
                while(l!=r){
                    arr[l] = 1;
                    l++;
                }
            }else{
                l = r;
            }
        }
        r++;
    }
}


void solve() {
    cin >> n >> q;
    vector<int> a(n);
    read(a);

    unordered_set<pair<int,int>, pair_hash> s;
    vector<ll> c0(n,0),c1(n,0);
    c0[0] = !a[0];
    c1[0] = a[0];
    for(int i=1;i<n;i++){
        c0[i] = c0[i-1] + !a[i];
        c1[i] = c1[i-1] + a[i];
    }
    vector<int> arr(n,0);
    alt(a, arr);
    vector<int> prefix(n);
    prefix[0] = arr[0];
    for(int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] + arr[i];
    }
    while(q--){
        cin>>x>>b;
        x--;
        b--;
        ll t0 = c0[b] - (x==0 ? 0 : c0[x-1]);
        ll t1 = c1[b] - (x==0 ? 0 : c1[x-1]);
        if(t0%3!=0 or t1%3!=0){
            cout<<-1<<"\n";
            continue;
        }
        ll sum  = prefix[b] - (x==0? 0 : prefix[x-1]);
        if(sum!=(b-x+1)){
            cout<< ( t0/3 ) + (t1/3) <<"\n";
        }else{
            cout<< ( t0/3 ) + (t1/3) + 1<<"\n";
        }
    }

}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}