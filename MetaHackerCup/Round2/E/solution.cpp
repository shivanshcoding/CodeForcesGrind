#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128 = __int128_t;
const int64 NEG64 = LLONG_MIN / 4;
const int DP_CAP = 1100000; // practical cap used in many contest solutions

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    for(int tc=1; tc<=T; ++tc){
        int N;
        int64 M;
        cin >> N >> M;
        vector<int64> A(N+1);
        for(int i=1;i<=N;i++) cin >> A[i];

        // prefix sums v[k] = A1 + ... + Ak
        vector<int64> v(N+1,0);
        for(int k=1;k<=N;k++) v[k] = v[k-1] + A[k];

        // trivial
        if(M <= 0){
            cout << "Case #" << tc << ": 0\n";
            for(int i=1;i<=N;i++) cout << 0 << (i==N?'\n':' ');
            continue;
        }

        // Choose best density B: maximize v[k]/k (tie-break smaller k)
        int B = 1;
        for(int k=2;k<=N;k++){
            i128 lhs = (i128)v[k] * B;
            i128 rhs = (i128)v[B] * k;
            if(lhs > rhs) B = k;
            else if(lhs == rhs && k < B) B = k;
        }
        int64 Pbest = v[B];
        if(Pbest <= 0){
            // Defensive: should not happen (Ai >= 1).
            cout << "Case #" << tc << ": 0\n";
            for(int i=1;i<=N;i++) cout << 0 << (i==N?'\n':' ');
            continue;
        }

        // DP limit: theoretical bound ~ B*B + B; cap to DP_CAP to keep run time bounded
        i128 wantL = (i128)B * B + B;
        int L = (int)min<i128>(wantL, (i128)DP_CAP);
        if(L < 0) L = 0;

        // DP arrays: dp[s] = max amaziness for exact bricks s (or NEG64 if unreachable)
        vector<int64> dp(L+1, NEG64);
        vector<int> parent(L+1, -1); // parent[s] stores item k used to reach dp[s]
        dp[0] = 0;

        // Unbounded knapsack (complete knapsack) by weight k (k <= L)
        for(int k=1;k<=N;k++){
            int w = k;
            if(w > L) continue;
            int64 val = v[k];
            if(val <= 0) continue;
            // iterate s from w..L (unbounded: forward order works because we consider unlimited times)
            for(int s = w; s <= L; ++s){
                if(dp[s - w] == NEG64) continue;
                int64 cand = dp[s - w] + val;
                if(cand > dp[s]){
                    dp[s] = cand;
                    parent[s] = k;
                }
            }
        }

        // Now compute best total bricks by trying each s = 0..L and adding q copies of B
        int64 best_total = LLONG_MAX;
        int best_s = -1;
        int64 best_q = 0;

        // also consider single-item solutions k where v[k] >= M (one-level)
        for(int k=1;k<=N;k++){
            if(v[k] >= M){
                if((int64)k < best_total){
                    best_total = k;
                    best_s = -k; // mark special single-k choice
                    best_q = 0;
                }
            }
        }

        // Try dp states
        for(int s=0; s<=L; ++s){
            if(dp[s] == NEG64) continue;
            if(dp[s] >= M){
                if((int64)s < best_total){
                    best_total = s;
                    best_s = s;
                    best_q = 0;
                }
            } else {
                // need q copies of best B to reach M
                i128 need = (i128)M - dp[s];
                i128 q = (need + Pbest - 1) / Pbest;
                i128 tot = (i128)s + q * (i128)B;
                if(tot < (i128)best_total){
                    best_total = (int64)tot;
                    best_s = s;
                    best_q = (int64)q;
                }
            }
        }

        // If nothing found (shouldn't), fallback to greedy using only B
        if(best_total == LLONG_MAX){
            i128 q = ( (i128)M + Pbest - 1) / Pbest;
            best_total = (int64)(q * (i128)B);
            best_s = 0;
            best_q = (int64)q;
        }

        // Reconstruct y[k] counts
        vector<int64> y(N+1, 0);
        if(best_s < 0){
            int k = -best_s;
            y[k] += 1;
        } else {
            int cur = best_s;
            while(cur > 0){
                int it = parent[cur];
                if(it <= 0) break; // safety (shouldn't happen)
                y[it] += 1;
                cur -= it;
            }
            if(best_q > 0) y[B] += best_q;
        }

        // Convert y -> x in O(N) by suffix sums: x[i] = sum_{k>=i} y[k]
        vector<int64> x(N+2, 0);
        for(int k=1;k<=N;k++) x[k] = y[k];
        for(int i=N-1;i>=1;--i) x[i] += x[i+1];

        // Output
        cout << "Case #" << tc << ": " << best_total << "\n";
        for(int i=1;i<=N;i++){
            cout << x[i] << (i==N?'\n':' ');
        }
    }
    return 0;
}
