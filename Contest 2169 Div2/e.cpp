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

class GeometryProcessor {
private:
    int N{};
    vector<ll> X, Y, C;

    // Read input arrays
    void readVectors() {
        X.resize(N);
        Y.resize(N);
        C.resize(N);
        for (auto &e : X) cin >> e;
        for (auto &e : Y) cin >> e;
        for (auto &e : C) cin >> e;
    }

    // Compute bounding rectangle perimeter
    ll boundingPerimeter(ll &minX, ll &maxX, ll &minY, ll &maxY) const {
        return 2 * (maxX - minX) + 2 * (maxY - minY);
    }

    // Maintain running extrema for special transformed expressions
    void updateTransforms(int i, ll &t1, ll &t2, ll &t3, ll &t4) const {
        ll xi = X[i], yi = Y[i], ci = C[i];
        t1 = max(t1,  (xi + yi) * 2 - ci);
        t2 = max(t2, -(xi + yi) * 2 - ci);
        t3 = max(t3,  (xi - yi) * 2 - ci);
        t4 = max(t4, -(xi - yi) * 2 - ci);
    }

public:
    ll processCase() {
        cin >> N;
        readVectors();

        if (N == 1) return 0;

        ll costSum = 0;
        ll loX = X[0], hiX = X[0];
        ll loY = Y[0], hiY = Y[0];

        ll bestF = LLONG_MIN;

        // transformed maxima
        ll T1 = LLONG_MIN, T2 = LLONG_MIN;
        ll T3 = LLONG_MIN, T4 = LLONG_MIN;

        for (int i = 0; i < N; ++i) {
            costSum += C[i];

            loX = min(loX, X[i]);
            hiX = max(hiX, X[i]);
            loY = min(loY, Y[i]);
            hiY = max(hiY, Y[i]);

            bestF = max(bestF, -C[i]);   // one-point selection

            updateTransforms(i, T1, T2, T3, T4);
        }

        // full rectangle choice
        ll fullPerim = boundingPerimeter(loX, hiX, loY, hiY);
        bestF = max(bestF, fullPerim - costSum);

        // two-extreme combination
        ll combo = max(T1 + T2, T3 + T4);
        bestF = max(bestF, combo);

        return costSum + bestF;
    }
};

int main() {
    fastio();

    int T;
    cin >> T;

    GeometryProcessor gp;

    while (T--) {
        cout << gp.processCase() << "\n";
    }
    return 0;
}
