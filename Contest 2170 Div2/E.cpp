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

static constexpr ll MOD = 998244353LL;

struct ModMath {
    static inline ll add(ll a, ll b) { a += b; if (a >= MOD) a -= MOD; return a; }
    static inline ll sub(ll a, ll b) { a -= b; if (a < 0) a += MOD; return a; }
    static inline ll mul(ll a, ll b) { return (a * b) % MOD; }
};

class IntervalManager {
public:
    IntervalManager(int mPos)
    : m(mPos), best(mPos + 2, mPos + 1), sufMin(mPos + 3, mPos + 1) {}

    void addInterval(int L, int R_inclusive_dec) {
        // R_inclusive_dec is already R-1 (matching user's semantics)
        if (L <= R_inclusive_dec && L >= 0 && L <= m) {
            best[L] = std::min(best[L], R_inclusive_dec);
        }
    }

    // compute suffix minima such that sufMin[i] = min(best[i], best[i+1], ...)
    void computeSuffix() {
        sufMin[m + 1] = m + 1;
        for (int i = m; i >= 1; --i) {
            sufMin[i] = std::min(best[i], sufMin[i + 1]);
        }
    }

    // accessor for suffix minima
    int suffixAt(int idx) const {
        if (idx <= m) return sufMin[idx];
        return m + 1;
    }

    int maxPos() const { return m; }

private:
    int m;
    vector<int> best;
    vector<int> sufMin;
};

class RangeDiffDP {
public:
    RangeDiffDP(int mPos)
    : m(mPos), diff(mPos + 6, 0), dp(mPos + 2, 0), running(0) {}

    void setBase(ll base) { dp[0] = base; }

    // apply add value to [L..R] range using difference array (clamped to [1..m])
    void addRange(int L, int R, ll value) {
        if (L > R) return;
        if (L < 1) L = 1;
        if (R > m) R = m;
        if (L > R) return;
        diff[L] = ModMath::add(diff[L], value);
        int endIdx = R + 1;
        if (endIdx < (int)diff.size()) diff[endIdx] = ModMath::sub(diff[endIdx], value);
    }

    // run DP filling dp[1..m] using pre-filled diff increments
    void run(const IntervalManager& im) {
        // initial behavior: apply ranges based on dp[0] has already been done by caller if needed
        for (int pos = 1; pos <= m; ++pos) {
            running = ModMath::add(running, diff[pos]);
            dp[pos] = running;

            int s = pos + 1;
            if (s <= m) {
                int e = im.suffixAt(s);
                if (e >= s) addRange(s, e, dp[pos]);
            }
        }
    }

    // collect number of "finishing" ways (states j where suffixAt(j+1) > m)
    ll collectWays(const IntervalManager& im) const {
        ll ways = 0;
        for (int j = 0; j <= m; ++j) {
            int s = j + 1;
            int val = (s <= m ? im.suffixAt(s) : m + 1);
            if (val > m) ways = ModMath::add(ways, dp[j]);
        }
        return ways;
    }

    // expose dp for debugging or other use (not used externally here)
    const vector<ll>& getDP() const { return dp; }

private:
    int m;
    vector<ll> diff;
    vector<ll> dp;
    ll running;
};

struct FastIn {
    FastIn() { ios::sync_with_stdio(false); cin.tie(nullptr); }
    bool readInt(int &x) { return bool(cin >> x); }
    template<class T> void readVec(vector<T>& v) { for (auto &e : v) cin >> e; }
};

struct Solver {
    void operator()() {
        FastIn in;
        int T;
        if (!in.readInt(T)) return;
        while (T--) solveCase();
    }

    void solveCase() {
        int n, intervalCount;
        cin >> n >> intervalCount;
        int mPos = n - 1;

        IntervalManager im(mPos);

        // read intervals: note that we preserve your last-paste semantics: R gets decremented
        for (int i = 0; i < intervalCount; ++i) {
            int L, R;
            cin >> L >> R;
            R = R - 1;        // keep the same behavior as in user's last submission
            im.addInterval(L, R);
        }

        im.computeSuffix();

        RangeDiffDP dpEngine(mPos);
        dpEngine.setBase(1);

        // initial transitions from dp[0] -> [1 .. suffixAt(1)]
        if (1 <= mPos) {
            int s = 1;
            int e = im.suffixAt(1);
            if (e >= s) dpEngine.addRange(s, e, 1);
        }

        dpEngine.run(im);

        ll ways = dpEngine.collectWays(im);
        ll ans = ModMath::mul(ways, 2);
        cout << ans << '\n';
    }
};

int main() {
    Solver solve;
    solve();
    return 0;
}
