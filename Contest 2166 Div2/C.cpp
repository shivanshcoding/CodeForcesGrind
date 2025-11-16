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

struct PQItem {
    ll value;
    int position;
};

struct PQComp {
    bool operator()(PQItem const& a, PQItem const& b) const {
        if (a.value != b.value) return a.value > b.value;
        return a.position > b.position;
    }
};

class CyclicMerger {
public:
    CyclicMerger() = default;

    // Compute minimal merge cost for one test case
    ll compute(int n, const vector<ll>& arr) {
        if (n == 2) return max(arr[0], arr[1]);

        // copy inputs to mutable members
        values = arr;
        size_t N = values.size();
        left.assign(N, 0);
        right.assign(N, 0);
        alive.assign(N, true);

        for (size_t i = 0; i < N; ++i) {
            left[i] = (int)((i + N - 1) % N);
            right[i] = (int)((i + 1) % N);
        }

        priority_queue<PQItem, vector<PQItem>, PQComp> pq;
        for (int i = 0; i < (int)N; ++i) pq.push(PQItem{values[i], i});

        ll total = 0;
        int merges = 0;
        const int want = (int)N - 1;

        while (merges < want) {
            PQItem cur = pq.top(); pq.pop();
            int idx = cur.position;

            // stale entry? skip
            if (!alive[idx]) continue;

            int l = left[idx];
            int r = right[idx];

            // choose the smaller neighbor to merge with
            int neighbor = (values[l] <= values[r]) ? l : r;

            // cost of merging idx and neighbor is the larger value
            ll cost = max(values[idx], values[neighbor]);
            total += cost;

            // we remove idx, and update neighbor's value to the merged value
            values[neighbor] = cost;
            alive[idx] = false;

            // unlink idx from ring
            int idxL = left[idx];
            int idxR = right[idx];
            right[idxL] = idxR;
            left[idxR] = idxL;

            // push updated neighbor value (may create stale entries later; handled above)
            pq.push(PQItem{values[neighbor], neighbor});

            ++merges;
        }

        return total;
    }

private:
    vector<ll> values;
    vector<int> left;
    vector<int> right;
    vector<char> alive; // char is lighter than bool in some implementations
};

int main() {
    fastio();

    if (!(cin >> t)) return 0;

    CyclicMerger solver;
    while (t--) {
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        cout << solver.compute(n, a) << '\n';
    }

    return 0;
}
