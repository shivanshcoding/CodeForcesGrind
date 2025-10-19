#include <bits/stdc++.h>
using namespace std;

// The custom hash is good practice for unordered_maps if needed.
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

const int MAX_A = 200005;
int spf[MAX_A + 2];

void sieve() {
    iota(spf, spf + MAX_A + 2, 0);
    for (int i = 2; i * i < MAX_A + 2; ++i) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j < MAX_A + 2; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

// Optimized to add to a vector instead of a set directly
void get_factors(int n, vector<int>& factors) {
    if (n <= 1) return;
    while (n > 1) {
        int p = spf[n];
        factors.push_back(p);
        while (n > 1 && spf[n] == p) {
            n /= p;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<long long> b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // --- OPTIMIZATION: Faster prime collection ---
    vector<int> candidate_primes_vec;
    for (int i = 0; i < n; ++i) {
        get_factors(a[i], candidate_primes_vec);
        if (a[i] > 1) {
            get_factors(a[i] - 1, candidate_primes_vec);
        }
        get_factors(a[i] + 1, candidate_primes_vec);
    }
    sort(candidate_primes_vec.begin(), candidate_primes_vec.end());
    candidate_primes_vec.erase(unique(candidate_primes_vec.begin(), candidate_primes_vec.end()), candidate_primes_vec.end());
    // --- End of Optimization ---

    long long min_total_cost = -1;

    for (int p : candidate_primes_vec) {
        long long min1 = -1, min2 = -1;

        for (int i = 0; i < n; ++i) {
            long long cost;
            if (a[i] % p == 0) {
                cost = 0;
            } else {
                cost = (long long)(p - (a[i] % p)) * b[i];
            }

            if (min1 == -1 || cost < min1) {
                min2 = min1;
                min1 = cost;
            } else if (min2 == -1 || cost < min2) {
                min2 = cost;
            }
        }

        if (min1 != -1 && min2 != -1) {
            long long current_total_cost = min1 + min2;
            if (min_total_cost == -1 || current_total_cost < min_total_cost) {
                min_total_cost = current_total_cost;
            }
        }
    }

    cout << min_total_cost << "\n";
}

int main() {
    sieve();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}