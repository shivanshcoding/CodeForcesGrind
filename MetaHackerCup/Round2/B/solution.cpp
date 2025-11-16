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
ll T=1,N,M,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;


ll solve() {
    cin >> N >> M;
    map<int, ll> sc;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        sc[a]++;
    }
    
    vector<ll> B(M);
    ll ta = 0;
    for (int i = 0; i < M; ++i) {
        cin >> B[i];
        ta += B[i];
    }

    vector<ll> C;
    for (auto const& [score, count] : sc) {
        C.push_back(count);
    }

    int D = C.size();
    if (D == 0) {
        return 0;
    }

    vector<ll> suffix_C(D + 1, 0);
    for (int i = D - 1; i >= 0; --i) {
        suffix_C[i] = suffix_C[i + 1] + C[i];
    }

    ll mr = 0, cn = 0;

    for (int p = D - 1; p >= 0; --p) {
        int k = D - p;
        
        cn = C[p] + cn + suffix_C[p + 1];

        if (k > M) {
            continue;
        }

        if (cn <= ta) {
            mr = max(mr, suffix_C[p]);
        }
    }

    return mr;
}

int main() {
    fastio();
    
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": " << solve() << endl;
    }
    return 0;
}