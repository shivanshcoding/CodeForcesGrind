#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;
const int LIM = 1'000'000;

struct NT {
    vector<int> spf, inv;
    NT(int n = LIM) {
        spf.assign(n + 1, 0);
        inv.assign(n + 1, 0);
        sieve(n);
        preinv(n);
    }
    void sieve(int n) {
        vector<int> pr;
        for (int i = 2; i <= n; i++) {
            if (!spf[i]) {
                spf[i] = i;
                pr.push_back(i);
            }
            for (int p : pr) {
                if (1LL * p * i > n) break;
                spf[p * i] = p;
                if (p == spf[i]) break;
            }
        }
        spf[1] = 1;
    }
    void preinv(int n) {
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
        }
    }
    ll modpow(ll a, ll e) const {
        ll r = 1 % MOD;
        while (e) {
            if (e & 1) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    }
    vector<pair<int,int>> factor(int n) const {
        vector<pair<int,int>> f;
        while (n > 1) {
            int p = spf[n], c = 0;
            while (n % p == 0) n /= p, c++;
            f.push_back({p, c});
        }
        return f;
    }
};

// helper to collect exponents into a vector
void collect(const vector<pair<int,int>> &f, vector<int> &cnt, vector<int> &list) {
    for (auto [p, c] : f) {
        if (cnt[p] == 0) list.push_back(p);
        cnt[p] += c;
    }
}

// main computation for a test case
ll solve_case(int x, int y, int z, const NT &nt) {
    static vector<int> exp(LIM + 1, 0);
    static vector<int> er(LIM + 1, 0);
    static vector<char> inM(LIM + 1, 0);

    vector<int> pm; pm.reserve(32);
    vector<int> touched; touched.reserve(64);

    // factorize x,y,z
    collect(nt.factor(x), exp, pm);
    collect(nt.factor(y), exp, pm);
    collect(nt.factor(z), exp, pm);

    ll ans = 1;
    for (int p : pm) {
        ans = ans * (p - 1) % MOD;
        ans = ans * nt.modpow(nt.inv[p], exp[p]) % MOD;
        inM[p] = 1;
    }

    for (int p : pm) {
        auto f = nt.factor(p - 1);
        for (auto [r, c] : f) {
            if (er[r] == 0) touched.push_back(r);
            er[r] += c;
        }
    }

    for (int r : touched) {
        if (inM[r]) {
            ans = ans * nt.modpow(nt.inv[r], er[r]) % MOD;
        } else {
            ll invr = nt.inv[r];
            ll term = (invr + ( (1 - invr + MOD) % MOD ) * nt.modpow(invr, er[r])) % MOD;
            ans = ans * term % MOD;
        }
    }

    // cleanup for reuse
    for (int p : pm) { exp[p] = 0; inM[p] = 0; }
    for (int r : touched) er[r] = 0;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    NT nt(LIM);

    int T; cin >> T;
    while (T--) {
        int x, y, z; cin >> x >> y >> z;
        cout << solve_case(x, y, z, nt) << "\n";
    }
}
