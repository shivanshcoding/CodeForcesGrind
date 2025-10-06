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

struct PrefixTool {
    vector<int> vals;
    PrefixTool(int n, const string& s) {
        vals.resize(n + 1);
        for (int i = 0; i < n; ++i) {
            vals[i + 1] = vals[i] + (s[i] == 'a' ? 1 : -1);
        }
    }
    int total() const { return vals.back(); }
    int size() const { return (int)vals.size() - 1; }
    int operator[](int i) const { return vals[i]; }
};

struct ShortRemover {
    const PrefixTool& pref;
    ShortRemover(const PrefixTool& p) : pref(p) {}

    int interior() const {
        unordered_map<int,int> seen;
        seen.reserve(pref.size()*2);
        seen[0] = 0;
        int target = pref.total();
        int best = INT_MAX;
        for (int j = 1; j <= pref.size(); ++j) {
            int need = pref[j] - target;
            auto it = seen.find(need);
            if (it != seen.end()) {
                best = min(best, j - it->second);
            }
            if (!seen.count(pref[j])) seen[pref[j]] = j;
        }
        return best == INT_MAX ? -1 : best;
    }

    int prefixRemove() const {
        int target = pref.total();
        for (int i = 1; i < pref.size(); ++i) {
            if (pref[i] == target) return i;
        }
        return -1;
    }

    int suffixRemove() const {
        for (int i = pref.size() - 1; i > 0; --i) {
            if (pref[i] == 0) return pref.size() - i;
        }
        return -1;
    }

    int solve() const {
        if (pref.total() == 0) return 0;
        int a = interior();
        int b = prefixRemove();
        int c = suffixRemove();
        int ans = INT_MAX;
        if (a != -1) ans = min(ans, a);
        if (b != -1) ans = min(ans, b);
        if (c != -1) ans = min(ans, c);
        if (ans == INT_MAX || ans == pref.size()) return -1;
        return ans;
    }
};

void processCase() {
    int n;
    string s;
    cin >> n >> s;
    PrefixTool tool(n, s);
    ShortRemover solver(tool);
    cout << solver.solve() << '\n';
}

int main() {
    fastio();
    cin >> t;
    while (t--) processCase();
    return 0;
}
