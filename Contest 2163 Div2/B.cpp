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


class FenwickMax {
    // 1-based Fenwick / BIT storing maximums on prefixes.
    vector<int> bit;
    int sz;

public:
    explicit FenwickMax(int n = 0) : bit(n + 1, 0), sz(n) {}

    void reset(int n) {
        bit.assign(n + 1, 0);
        sz = n;
    }

    // set position idx to max(current, val)
    void relax(int idx, int val) {
        for (; idx <= sz; idx += idx & -idx) {
            if (bit[idx] < val) bit[idx] = val;
        }
    }

    int prefMax(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            if (bit[idx] > res) res = bit[idx];
        }
        return res;
    }
};


class Solver {
    int n;
    vector<int> perm;
    string mask;

    vector<int> incEnd, decEnd, incStart, decStart;
    int posVal1, posValN;

public:
    Solver(): n(0), posVal1(-1), posValN(-1) {}

    void readCase() {
        cin >> n;
        perm.assign(n, 0);
        posVal1 = posValN = -1;
        for (int i = 0; i < n; ++i) {
            cin >> perm[i];
            if (perm[i] == 1) posVal1 = i;
            if (perm[i] == n) posValN = i;
        }
        cin >> mask;
    }

    void buildSequences() {
        incEnd.assign(n, 0);
        decEnd.assign(n, 0);
        incStart.assign(n, 0);
        decStart.assign(n, 0);

        // 1) LIS ending at i (based on values < perm[i])
        FenwickMax fw(n);
        for (int i = 0; i < n; ++i) {
            int best = fw.prefMax(perm[i] - 1);
            incEnd[i] = best + 1;
            fw.relax(perm[i], incEnd[i]);
        }

        // 2) "LDS" ending at i by mapping value -> inverted value
        FenwickMax fw2(n);
        for (int i = 0; i < n; ++i) {
            int inv = n + 1 - perm[i];
            int best = fw2.prefMax(inv - 1);
            decEnd[i] = best + 1;
            fw2.relax(inv, decEnd[i]);
        }

        // 3) LIS starting at i (r > i, p[r] > p[i])
        // using inverted mapping as in original code
        FenwickMax fw3(n);
        for (int i = n - 1; i >= 0; --i) {
            int inv = n + 1 - perm[i];
            int best = fw3.prefMax(inv - 1);
            incStart[i] = best + 1;
            fw3.relax(inv, incStart[i]);
        }

        // 4) LDS starting at i (r > i, p[r] < p[i])
        FenwickMax fw4(n);
        for (int i = n - 1; i >= 0; --i) {
            int best = fw4.prefMax(perm[i] - 1);
            decStart[i] = best + 1;
            fw4.relax(perm[i], decStart[i]);
        }
    }

    bool feasibilityCheck() const {
        for (int i = 0; i < n; ++i) {
            if (mask[i] == '1') {
                bool incPossible = (incEnd[i] > 1 && incStart[i] > 1);
                bool decPossible = (decEnd[i] > 1 && decStart[i] > 1);
                if (!incPossible && !decPossible) return false;
            }
        }
        return true;
    }

    void produceOutput() const {
        if (!feasibilityCheck()) {
            cout << "-1\n";
            return;
        }

        // exactly the same 5-operations scheme as original solution
        cout << "5\n";
        int L = min(posVal1, posValN);
        int R = max(posVal1, posValN);

        // print 1-based indices like original
        cout << (L + 1) << ' ' << (R + 1) << '\n';
        cout << 1 << ' ' << (L + 1) << '\n';
        cout << 1 << ' ' << (R + 1) << '\n';
        cout << (L + 1) << ' ' << n << '\n';
        cout << (R + 1) << ' ' << n << '\n';
    }

    void solveOne() {
        readCase();
        buildSequences();
        produceOutput();
    }
};


int main() {
    fastio();
    if (!(cin >> t)) return 0;
    Solver solver;
    while (t--) solver.solveOne();

    return 0;
}
