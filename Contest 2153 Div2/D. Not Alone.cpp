#include <bits/stdc++.h>
using namespace std;
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

constexpr ll BIGVAL = 4e18;

// small inline lambda for triple spread
auto spread = [](ll a, ll b, ll c) -> ll {
    ll hi = a, lo = a;
    hi = max(hi, b);
    hi = max(hi, c);
    lo = min(lo, b);
    lo = min(lo, c);
    return hi - lo;
};

// Computes minimum path cost through array pattern
struct Evaluator {
    ll compute(const vector<ll> &seq) {
        int sz = (int)seq.size();
        if (!sz) return 0;

        vector<ll> best(sz + 4, BIGVAL);
        best[0] = 0;

        for (int i = 1; i <= sz; ++i) {
            if (i > 1 && best[i - 2] != BIGVAL) {
                ll step = abs(seq[i - 1] - seq[i - 2]);
                best[i] = min(best[i], best[i - 2] + step);
            }
            if (i > 2 && best[i - 3] != BIGVAL) {
                ll add = spread(seq[i - 1], seq[i - 2], seq[i - 3]);
                best[i] = min(best[i], best[i - 3] + add);
            }
        }
        return best[sz];
    }
};

// The main logic controller
class Engine {
public:
    void run_case() {
        int n;
        cin >> n;
        vector<ll> arr(n);
        for (auto &x : arr) cin >> x;

        Evaluator eval;
        ll ans = eval.compute(arr);

        auto try_case = [&](int left, int right, function<ll(int,int,int)> fn) -> void {
            if (right <= left) return;
            vector<ll> slice(arr.begin() + left, arr.begin() + right);
            ll subcost = eval.compute(slice);
            if (subcost == BIGVAL) return;
            ans = min(ans, subcost + fn(left, right, n));
        };

        if (n >= 2) {
            try_case(1, n - 1, [&](int, int, int N) {
                return abs(arr[0] - arr[N - 1]);
            });
        }
        if (n >= 3) {
            try_case(1, n - 2, [&](int, int, int N) {
                return spread(arr[N - 2], arr[N - 1], arr[0]);
            });
            try_case(2, n - 1, [&](int, int, int) {
                return spread(arr[n - 1], arr[0], arr[1]);
            });
        }

        cout << ans << '\n';
    }
};

int main() {
    fastio();
    cin >> t;
    Engine solver;
    while (t--) solver.run_case();
    return 0;
}
