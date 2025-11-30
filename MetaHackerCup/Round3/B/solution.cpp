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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    for(int tc=1;tc<=T;++tc){
        int N;
        cin>>N;
        vector<ll>A(N+1);
        for(int i=1;i<=N;++i) cin>>A[i];
        vector<int>B(N+1);
        for(int i=1;i<=N;++i) cin>>B[i];
        vector<int>M(N+1,0);
        for(int i=1;i<=N;++i){
            M[i]=max(M[i-1],B[i]);
        }
        int K = M[N];
        if(K==0){
            cout<<"Case #"<<tc<<": 0\n";
            continue;
        }
        vector<int> pos(K+1, N+1);
        for(int k=1;k<=K;++k){
            for(int i=1;i<=N;++i) if(M[i]>=k){ pos[k]=i; break; }
        }
        vector<ll>pref(N+1,0);
        for(int i=1;i<=N;++i) pref[i]=pref[i-1]+A[i];
        const ll INF = (ll)9e18;
        vector<ll> dp(K+1, INF);
        dp[0]=0;
        int kptr = K;
        for(int r=1;r<=N;++r){
            while(kptr>0 && pos[kptr] < r) --kptr;
            int Kr = kptr;
            if(Kr==0) continue;
            vector<ll> minPref(K+1);
            minPref[0]=dp[0];
            for(int i=1;i<=K;++i) minPref[i]= std::min(minPref[i-1], dp[i]);
            // int upto = min(r, Kr);
            ll minTail = INF;
            // handle L from upto downwards to compute tail min for t1==Kr
            for(int L = r; L>=1; --L){
                ll cost = pref[r] - pref[r-L];
                if(L>=Kr){
                    if(cost < minTail) minTail = cost;
                } else {
                    int t1 = L;
                    ll base = minPref[t1-1];
                    if(base<INF){
                        ll cand = base + cost;
                        if(cand < dp[t1]) dp[t1] = cand;
                    }
                }
                if(L==1) break;
                if(L-1 < 1) break;
            }
            if(minTail < INF){
                ll base = minPref[Kr-1];
                if(base<INF){
                    ll cand = base + minTail;
                    if(cand < dp[Kr]) dp[Kr] = cand;
                }
            }
        }
        ll ans = dp[K];
        if(ans==INF) ans = -1;
        cout<<"Case #"<<tc<<": "<<ans<<"\n";
    }
    return 0;
}
