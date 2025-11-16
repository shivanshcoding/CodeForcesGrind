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

constexpr ll NEG_INF = LLONG_MIN;

struct PackedArray {
    vector<ll> data; // descending sorted
    int n;
    PackedArray() : n(0) {}
    PackedArray(vector<ll> v) {
        data = std::move(v);
        sort(data.begin(), data.end(), greater<ll>());
        n = (int)data.size();
    }

    // return last index with value >= x, or -1 if none
    int last_index_ge(ll x) const {
        if (n == 0 || data[0] < x) return -1;
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (data[mid] >= x) lo = mid + 1;
            else hi = mid;
        }
        return lo - 1;
    }
};

struct QueryAllocator {
    const PackedArray& arr;
    int N;
    // residues[i] == NEG_INF => index i not yet used
    vector<ll> residues;
    vector<int> active_list; // indices that are present in residues
    int ptr; // first unused index (scans forward)
    QueryAllocator(const PackedArray& a)
        : arr(a), N(a.n), residues(a.n, NEG_INF), ptr(0) {}

    // advance ptr to first index not present in residues
    void advance_ptr() {
        while (ptr < N && residues[ptr] != NEG_INF) ++ptr;
    }

    // mark index idx as active (if not already), optionally set residue
    void ensure_active(int idx, ll rem = NEG_INF) {
        if (residues[idx] == NEG_INF) {
            residues[idx] = rem;
            active_list.push_back(idx);
            if (idx == ptr) {
                ++ptr;
                advance_ptr();
            }
        } else {
            // already active: optionally overwrite residue if rem != NEG_INF
            if (rem != NEG_INF) residues[idx] = rem;
        }
    }
};

struct Solver {
    void run() {
        fastio();
        if (!(cin >> t)) return;
        while (t--) solve_case();
    }

    void solve_case() {
        cin >> n >> q;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        PackedArray packed(move(a));
        for (int qi = 0; qi < q; ++qi) {
            ll c; cin >> c;
            cout << process_one_query(packed, c) << '\n';
        }
    }

    // EXACT logic translation of provided algorithm
    ll process_one_query(const PackedArray& packed, ll c) {
        QueryAllocator allocator(packed);

        // gather sizes for set bits in c (largest bits first)
        vector<ll> sizes;
        for (int bit = 30; bit >= 0; --bit) {
            if ((c >> bit) & 1LL) sizes.push_back(1LL << bit);
        }

        ll total_added = 0;

        for (ll sz : sizes) {
            int k = packed.last_index_ge(sz);

            // If there exists an unused original element >= sz at position ptr..k, use ptr
            if (allocator.ptr < allocator.N && k >= allocator.ptr) {
                ll rem = packed.data[allocator.ptr] - sz;
                allocator.ensure_active(allocator.ptr, rem);
                allocator.advance_ptr();
                continue;
            }

            // try to find an active index whose residue >= sz, pick the one with max residue
            int best_idx = -1;
            ll best_rem = NEG_INF;
            for (int id : allocator.active_list) {
                ll r = allocator.residues[id];
                if (r >= sz && r > best_rem) {
                    best_rem = r;
                    best_idx = id;
                }
            }
            if (best_idx != -1) {
                allocator.residues[best_idx] -= sz;
                continue;
            }

            // otherwise we will choose the index with maximum residue among active ones or the current ptr
            ll rem_ptr = (allocator.ptr < allocator.N ? packed.data[allocator.ptr] : NEG_INF);
            int idx_max = -1;
            ll rem_max = rem_ptr;
            if (rem_ptr != NEG_INF) idx_max = allocator.ptr;

            for (int id : allocator.active_list) {
                ll r = allocator.residues[id];
                if (r > rem_max) {
                    rem_max = r;
                    idx_max = id;
                }
            }

            if (idx_max == -1) idx_max = 0; // follow original fallback

            ll increment = sz - rem_max;
            if (increment < 0) increment = 0;
            total_added += increment;

            // make sure idx_max is active and set its residue to 0 (we filled it exactly)
            if (allocator.residues[idx_max] == NEG_INF) {
                allocator.ensure_active(idx_max, 0);
            } else {
                allocator.residues[idx_max] = 0;
            }
        }

        return total_added;
    }
};

int main() {
    Solver s;
    s.run();
    return 0;
}
