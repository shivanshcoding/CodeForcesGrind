#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fenwick Tree adapted for prefix maximum
struct FenwickMax {
    int n;
    vector<int> bit;
    FenwickMax(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    // update position idx with value val (max operation)
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] = max(bit[idx], val);
    }

    // query maximum in [1..idx]
    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res = max(res, bit[idx]);
        return res;
    }

    // query maximum in [l..n]
    int querySuffix(int l) {
        if (l > n) return 0;
        return query(n) - 0, query(n) >= query(l-1) ? query(n) : query(n); // fixed below
    }
};

// Helper: suffix query [l..n]
int querySuffix(FenwickMax &fw, int l) {
    if (l <= 0) return fw.query(fw.n);
    if (l > fw.n) return 0;
    // Trick: we reversed indices by mapping x -> n - x + 1, 
    // so suffix query becomes prefix query
    return fw.query(l);
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> A(n + 1), B(n + 1);
        for (int i = 1; i <= n; i++) cin >> A[i];
        for (int i = 1; i <= n; i++) cin >> B[i];

        int maxVal = 2 * n + 5;

        // We flip indices: newIndex = maxVal - val + 1
        FenwickMax fw(maxVal + 2);

        ll answer = 0;
        for (int i = 1; i <= n; i++) {
            int idxA = maxVal - A[i] + 1;
            int idxB = maxVal - B[i] + 1;

            int prev_ge_a = fw.query(idxA); // corresponds to [A[i]..maxVal]
            int prev_ge_b = fw.query(idxB);

            ll count = 0;
            if (A[i] == B[i]) {
                count = i;
            } else if (B[i] < A[i]) {
                count = prev_ge_a;
            } else {
                count = prev_ge_b;
            }

            answer += count * 1LL * (n - i + 1);

            fw.update(idxA, i);
        }
        cout << answer << "\n";
    }
}

int main() {
    solve();
    return 0;
}
