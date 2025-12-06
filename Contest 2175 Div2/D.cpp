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
const ll INF_SCORE = -1, MOD = 1e9+7, INF_IDX = 1e9;

struct State {
    int mind;
    ll maxi;
};

void solve() {
    cin>>n>>k;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<vector<ll>> dp(n+2, vector<ll> (k+1,n+1));
    int v = 1;
    while(v<=k){
        for(int i=n;i>=1;i--){
            if(a[i]<v){
                dp[i][v] = dp[i+1][v];
            }else{
                dp[i][v] = i;
            }
        }
        v++;
    }
    vector<vector<State>> dp2(k+1, vector<State>(k+1,{INF_IDX,INF_SCORE}));
    dp2[0][0] = {0, 0};

    ll res = 0;
    vector<pll> vs;
    vs.push_back({0, 0});

    // max sts is 27 -> k=360
    for (int st =1;st <=27;st++) {
        vector<vector<State>> dp3(k+1, vector<State>(k+1, {INF_IDX,INF_SCORE}));
        vector<pll> vs2;
        bool flag = false;

        for (auto& p : vs) {
            int cost = p.f,val = p.s;
            
            ll curr_i = dp2[cost][val].mind,curr_s = dp2[cost][val].maxi;
            for (int nv = val + 1; cost + nv <= k; ++nv) {
                int next_cost = cost + nv;
                
                int ni = dp[curr_i+1][nv];
                if (ni >n) continue;

                ll add_s = (ll)(nv-val)*(n -ni+1);
                ll new_s = curr_s+add_s;

                State& t = dp3[next_cost][nv];
                if (t.mind==INF_IDX) {
                    t = {ni,new_s};
                    vs2.push_back({next_cost,nv});
                    flag = true;
                } else {
                    if (ni<t.mind) {
                        t={ni, new_s}; 
                    } else if (ni==t.mind) {
                        t.maxi = max(t.maxi,new_s);
                    }
                }
                res = max(res,t.maxi);
            }
        }

        if (!flag) break;
        dp2 = dp3;
        vs = vs2;
    }

    cout<<res<<"\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}