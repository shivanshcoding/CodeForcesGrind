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
const ll MAX_EXP = 65; 


ll fact[MAX_EXP];
ll invFact[MAX_EXP];

ll N_val, A_val;
vector<pair<ll, int>> pf_B;
vector<pair<ll, int>> pf_d;
ll total_ans;

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}


ll modInverse(ll n) {
    return power(n, MOD - 2);
}


void precompute_factorials() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAX_EXP; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

ll combinations(int k, ll N) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    ll N_mod = N % MOD;
    ll num = 1;
    for (int i = 0; i < k; ++i) {
        num = (num * ((N_mod + i) % MOD)) % MOD;
    }
    return (num * invFact[k]) % MOD;
}

ll count_ways(const vector<pair<ll, int>>& prime_factors, ll N) {
    ll res = 1;
    for (auto const& [p, e] : prime_factors) {
        res = (res * combinations(e, N)) % MOD;
    }
    return res;
}


void generate_divisors_and_calculate(int k, ll current_d) {
    if (k == (int)pf_B.size()) {
        if (current_d > A_val) {
            return;
        }

        vector<pair<ll, int>> pf_comp;
        for (size_t i = 0; i < pf_B.size(); ++i) {
            if (pf_B[i].second - pf_d[i].second > 0) {
                 pf_comp.push_back({pf_B[i].first, pf_B[i].second - pf_d[i].second});
            }
        }

        ll ways1 = count_ways(pf_d, N_val);
        ll ways2 = count_ways(pf_comp, N_val);

        total_ans = (total_ans + (ways1 * ways2) % MOD) % MOD;
        return;
    }

    ll p = pf_B[k].first;
    int max_exp = pf_B[k].second;
    ll p_power = 1;

    for (int i = 0; i <= max_exp; ++i) {
        if ((double)A_val / p_power < current_d) {
            break;
        }
        
        pf_d.push_back({p, i});
        generate_divisors_and_calculate(k + 1, current_d * p_power);
        pf_d.pop_back();

        if (i < max_exp) {
            p_power *= p;
        }
    }
}

void solve() {
    ll B_val;
    cin >> N_val >> A_val >> B_val;

    pf_B.clear();
    ll temp_B = B_val;
    for (ll i = 2; i * i <= temp_B; ++i) {
        if (temp_B % i == 0) {
            int count = 0;
            while (temp_B % i == 0) {
                temp_B /= i;
                count++;
            }
            pf_B.push_back({i, count});
        }
    }
    if (temp_B > 1) {
        pf_B.push_back({temp_B, 1});
    }

    total_ans = 0;
    pf_d.clear();
    generate_divisors_and_calculate(0, 1);
    cout << total_ans << "\n";
}

int main() {
    fastio();
    precompute_factorials();

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}