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


using i128 = __int128_t;
using u64  = unsigned long long;

static constexpr u64 GLOBAL_LIMIT = 1'000'000'000'000ULL;

class PlateauStepper {
    u64 limit_;

    // Safe clamp to the cap (limit_)
    inline i128 clamp(i128 v) const {
        if (v > (i128)limit_) return (i128)limit_;
        return v;
    }

public:
    PlateauStepper(u64 cap = GLOBAL_LIMIT) : limit_(cap) {}

    // Core evolution: apply `steps` iterations of x -> x + floor(x / d)
    // starting with initial = n. Behavior identical to previous phi_pow_capped.
    i128 evolve(i128 initial, i128 steps, i128 d) const {
        if (d == 0) return (i128)limit_;
        i128 x = initial;

        while (steps > 0 && x < (i128)limit_) {
            if (x < d) break;             // floor(x/d) == 0 -> fixed point

            i128 q = x / d;               // increment per step in current plateau (>=1)
            // next boundary where floor(x/d) increases
            i128 nextThreshold = (q + 1) * d;
            i128 distance = nextThreshold - x; // positive, <= d

            // steps needed to reach or cross the threshold at rate q
            // ceil(distance / q)
            i128 need = (distance + q - 1) / q;

            if (steps <= need) {
                x += q * steps;
                steps = 0;
            } else {
                x += q * need;
                steps -= need;
            }
        }

        return clamp(x);
    }
};

static inline u64 func1(i128 value) {
    if (value >= (i128)GLOBAL_LIMIT) return ULLONG_MAX; // sentinel for -1
    return (u64)(value + 1); // final answer is result + 1
}

static bool read_u64(u64 &out) {
    if (!(cin >> out)) return false;
    return true;
}

int main() {
    fastio();

    if (!(cin >> t)) return 0;

    PlateauStepper engine(GLOBAL_LIMIT);

    while (t--) {
        u64 X, Y, K;
        read_u64(X);
        read_u64(Y);
        read_u64(K);

        if (Y == 1ULL) {
            cout << -1 << '\n';
            continue;
        }

        // initial count is K-1, simulate X steps of n -> n + floor(n/(Y-1))
        i128 n0 = (i128)K - 1;
        i128 denom = (i128)Y - 1;
        i128 after = engine.evolve(n0, (i128)X, denom);

        if (after >= (i128)GLOBAL_LIMIT) {
            cout << -1 << '\n';
        } else {
            // answer prints after + 1 as unsigned long long
            cout << (u64)(after + 1) << '\n';
        }
    }

    return 0;
}
