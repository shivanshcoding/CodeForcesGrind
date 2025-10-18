#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAX_EXP = 65; // Max possible exponent for a prime factor of a number <= 10^14

// Precomputed factorials and their modular inverses
ll fact[MAX_EXP];
ll invFact[MAX_EXP];

// Globals for the recursive solver
ll N_val, A_val;
vector<pair<ll, int>> pf_B; // Prime factorization of B
vector<pair<ll, int>> pf_d; // Prime factorization of the current divisor d
ll total_ans;

// Function for modular exponentiation (to find modular inverse)
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

// Function to calculate modular inverse using Fermat's Little Theorem
ll modInverse(ll n) {
    return power(n, MOD - 2);
}

// Precompute factorials and their inverses up to MAX_EXP
void precompute_factorials() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAX_EXP; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

// Calculates C(N+k-1, k) % MOD efficiently for large N
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

// Calculates the number of ways to form a product from N multipliers,
// given its prime factorization.
ll count_ways(const vector<pair<ll, int>>& prime_factors, ll N) {
    ll res = 1;
    for (auto const& [p, e] : prime_factors) {
        res = (res * combinations(e, N)) % MOD;
    }
    return res;
}

// Recursively generates all divisors of B, and for each valid one,
// calculates its contribution to the total answer.
void generate_divisors_and_calculate(int k, ll current_d) {
    // Base case: we have constructed a full divisor d
    if (k == (int)pf_B.size()) {
        // Condition: coolness after N days (d) must be <= A
        if (current_d > A_val) {
            return;
        }

        // Calculate prime factors of the complementary divisor B/d
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

    // Iterate through all powers of the current prime factor
    for (int i = 0; i <= max_exp; ++i) {
        // Pruning: if current_d * p_power would exceed A, stop.
        // Using double division to avoid overflow with large numbers.
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

    // Prime factorize B
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute_factorials();

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}