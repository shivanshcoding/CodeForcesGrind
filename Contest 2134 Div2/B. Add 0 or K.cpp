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
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
using ld = long double;
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }


using int64 = long long;

namespace {
    // Fast pow (a^e mod m) – works for prime m in this use-case.
    int64 mod_pow(int64 a, int64 e, int64 m) {
        int64 r = 1 % m;
        a %= m;
        while (e > 0) {
            if (e & 1) r = (__int128)r * a % m;
            a = (__int128)a * a % m;
            e >>= 1;
        }
        return r;
    }

    // Smallest prime factor of x (x >= 2)
    int64 smallest_prime_factor(int64 x) {
        if (x % 2 == 0) return 2;
        for (int64 d = 3; d * d <= x; d += 2) {
            if (x % d == 0) return d; // the first divisor is prime
        }
        return x; // x itself is prime
    }

    // Normalize a[i] so that (a[i] + m*k) % p == 0 for minimal m in [0, p-1]
    void normalize_vector(vector<int64>& v, int64 k, int64 p) {
        // Since p | (k+1), gcd(k, p) == 1 and k has a modular inverse mod p.
        int64 inv_k = mod_pow((k % p + p) % p, p - 2, p); // Fermat's little theorem

        transform(v.begin(), v.end(), v.begin(), [&](int64 val) -> int64 {
            int64 s = ((p - (val % p + p) % p) % p);   // needed residue to hit 0
            int64 m = (__int128)s * inv_k % p;         // steps of k to add
            return val + m * k;
        });
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int64 n, k;
        cin >> n >> k;

        vector<int64> a(n);
        for (auto& x : a) cin >> x;

        const int64 p = smallest_prime_factor(k + 1);
        // k % p can never be 0 here because p | (k+1) ⇒ k ≡ -1 (mod p)
        normalize_vector(a, k, p);

        for (int i = 0; i < (int)a.size(); ++i) {
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}
