#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 MOD = 998244353;

// global memo for current DP run
unordered_map<uint64_t, int64> memo;
string S;
int K, N;

// combine state into 64-bit key
// mask: bits 0..K-1 (<=25 bits), rem: up to 5 bits, pos: up to 11 bits (pos<=2025 but we only use for len<=K), started:1 bit
inline uint64_t make_key(int pos, int rem, uint32_t mask, bool started) {
    // layout: lower bits mask (up to 25), then rem (6 bits), pos (10 bits), started (1 bit)
    // ensure bit widths big enough:
    uint64_t key = mask;
    key |= (uint64_t)rem << 32;       // rem in bits 32..37
    key |= (uint64_t)pos << 40;       // pos in bits 40..50
    key |= (uint64_t)started << 52;   // started in bit 52
    return key;
}

// dfs counts numbers <= S (given by tight flag), that are NOT K-weak, modulo MOD
int64 dfs(int pos, int rem, uint32_t mask, bool tight, bool started) {
    if (pos == N) {
        // count only positive integers
        return started ? 1 : 0;
    }
    if (!tight) {
        uint64_t key = make_key(pos, rem, mask, started);
        auto it = memo.find(key);
        if (it != memo.end()) return it->second;
        int64 ans = 0;
        for (int dig = 0; dig <= 9; ++dig) {
            bool nstarted = started || (dig != 0);
            if (!nstarted) {
                // still leading zeros; residue remains 0 and mask remains (bit0 set)
                ans += dfs(pos+1, 0, mask, false, false);
                if (ans >= MOD) ans -= MOD;
            } else {
                int nrem = (rem + dig) % K;
                // if residue already seen => repeat => it's K-weak -> do NOT count this branch in NOT-weak count
                if ( (mask >> nrem) & 1u ) {
                    // branch is K-weak -> skip (counts 0)
                    continue;
                } else {
                    uint32_t nmask = mask | (1u << nrem);
                    ans += dfs(pos+1, nrem, nmask, false, true);
                    if (ans >= MOD) ans -= MOD;
                }
            }
        }
        memo[key] = ans;
        return ans;
    } else {
        int limit = S[pos] - '0';
        int64 ans = 0;
        for (int dig = 0; dig <= limit; ++dig) {
            bool ntight = tight && (dig == limit);
            bool nstarted = started || (dig != 0);
            if (!nstarted) {
                ans += dfs(pos+1, 0, mask, ntight, false);
                if (ans >= MOD) ans -= MOD;
            } else {
                int nrem = (rem + dig) % K;
                if ( (mask >> nrem) & 1u ) {
                    continue;
                } else {
                    uint32_t nmask = mask | (1u << nrem);
                    ans += dfs(pos+1, nrem, nmask, ntight, true);
                    if (ans >= MOD) ans -= MOD;
                }
            }
        }
        return ans;
    }
}

// count numbers in [1, S] that are NOT K-weak (mod MOD)
int64 count_not_weak_up_to(string s, int k) {
    if (s == "0") return 0;
    S = s; K = k; N = (int)S.size();
    memo.clear();
    // initial: pos=0, rem=0, mask has bit 0 set because prefix p0 = 0 is seen
    uint32_t init_mask = 1u << 0;
    int64 res = dfs(0, 0, init_mask, true, false);
    return res % MOD;
}

// compute big integer value of string s modulo MOD
int64 str_mod(const string &s) {
    int64 r = 0;
    for (char c : s) {
        r = (r * 10 + (c - '0')) % MOD;
    }
    return r;
}

// compute (R - L + 1) mod MOD where R,L are decimal strings, R>=L
int64 range_count_mod(const string &R, const string &L) {
    // compute R mod MOD and L mod MOD
    int64 rm = str_mod(R);
    int64 lm = str_mod(L);
    int64 ans = (rm - lm + 1) % MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

// decrement decimal string by 1, assume s >= "1"
string dec_str(const string &s) {
    string t = s;
    int i = (int)t.size()-1;
    while (i>=0) {
        if (t[i]>'0') { t[i]--; break; }
        else { t[i]='9'; i--; }
    }
    // strip leading zeros if any (but ensure at least "0")
    int pos = 0;
    while (pos+1 < (int)t.size() && t[pos]=='0') pos++;
    if (pos>0) t = t.substr(pos);
    return t;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        string L, R;
        int k;
        cin >> L >> R >> k;
        K = k;
        // total numbers in [L,R] modulo MOD
        int64 total_mod = range_count_mod(R, L);

        // count NOT-weak ≤ R and ≤ L-1
        int64 notR = 0, notLminus1 = 0;

        if ((int)R.size() >= K) {
            // all numbers of length >= K are K-weak, so any non-weak number ≤ R must have length < K
            // our DP handles it correctly; we still run it (but it will explore up to pos==len(R)).
            // However, to speed up, we can restrict S to min(R, 10^{K}-1) by truncation: easiest is to run DP as is.
            notR = count_not_weak_up_to(R, K);
        } else {
            notR = count_not_weak_up_to(R, K);
        }

        string Lm1 = dec_str(L);
        if (Lm1 == "0") {
            notLminus1 = 0;
        } else {
            notLminus1 = count_not_weak_up_to(Lm1, K);
        }

        int64 not_in_range = (notR - notLminus1) % MOD;
        if (not_in_range < 0) not_in_range += MOD;

        int64 weak_mod = (total_mod - not_in_range) % MOD;
        if (weak_mod < 0) weak_mod += MOD;

        cout << "Case #" << tc << ": " << weak_mod << "\n";
    }
    return 0;
}
