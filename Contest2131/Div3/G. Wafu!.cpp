#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

map<ll, ll> dp; // H() ka memoization

// (base^exp) % MOD - fast exponentiation
ll tezPower(ll aadhaar, ll ghat) {
    ll jawab = 1;
    aadhaar %= MOD;
    while (ghat > 0) {
        if (ghat & 1) jawab = (jawab * aadhaar) % MOD; // bit set hai to multiply
        aadhaar = (aadhaar * aadhaar) % MOD; // square karo
        ghat >>= 1; // next bit
    }
    return jawab;
}

// given k, product P nikalna
ll nikalP(ll k) {
    if (k == 0) return 1;
    ll jawab = 1;
    for (ll p = 0; p < 60; p++) {
        ll term = 1LL << p; // 2^p
        if (term > k) break;
        ll baar = (k / term + 1) / 2; // kitni baar factor aayega
        if (baar == 0) continue;
        jawab = (jawab * tezPower(p + 1, baar)) % MOD;
    }
    return jawab;
}

// H(g) ka value nikalna (recursive + memo)
ll nikalH(ll g) {
    if (g <= 1) return 1;
    if (dp.count(g)) return dp[g];
    ll pehle = nikalH(g - 1);
    ll jawab = (g - 1) * pehle % MOD * pehle % MOD;
    return dp[g] = jawab;
}

void halKaro() {
    int gin; // n ka value
    ll k;    // k ka value
    cin >> gin >> k;

    set<ll> alag; // unique values ka set
    for (int i = 0; i < gin; i++) {
        ll x;
        cin >> x;
        alag.insert(x);
    }

    // sabse chhota missing number g nikalna
    ll g = 1;
    while (alag.count(g)) g++;

    // events list me g and baaki bade wale values daal do
    vector<ll> ghatna; 
    ghatna.push_back(g);
    for (ll x : alag) {
        if (x >= g) ghatna.push_back(x);
    }

    ll jawab = 1;

    // events process karte hain jab tak k bacha hai
    for (size_t i = 0; i < ghatna.size(); i++) {
        if (k == 0) break;

        ll abhiG = ghatna[i];

        // agar g > 1 hai to dekhte hain kitne operations chahiye
        if (abhiG > 1) {
            ll chahiyeOps = -1;
            if (abhiG - 1 < 31) {
                chahiyeOps = (1LL << (abhiG - 1)) - 1; // 2^(g-1) - 1
            }

            if (chahiyeOps != -1 && k >= chahiyeOps) {
                k -= chahiyeOps;
                jawab = (jawab * nikalH(abhiG)) % MOD;
            } else {
                jawab = (jawab * nikalP(k)) % MOD;
                k = 0;
                break;
            }
        }

        if (k == 0) break;

        // next event ke saath multiply
        if (i + 1 < ghatna.size()) {
            k--;
            jawab = (jawab * ghatna[i + 1]) % MOD;
        } else {
            jawab = (jawab * nikalP(k)) % MOD;
            k = 0;
        }
    }

    cout << jawab << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testCases;
    cin >> testCases;
    while (testCases--) {
        halKaro();
    }
    return 0;
}
