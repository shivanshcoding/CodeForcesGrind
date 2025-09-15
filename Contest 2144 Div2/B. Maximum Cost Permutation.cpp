#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF64 = (1LL << 60);
const int MOD = 1e9 + 7;

// ---------------- Helper Functions ---------------- //

// Reads the input array and fills counters
tuple<vector<int>, unordered_set<int>, int> read_input(int n) {
    vector<int> a(n + 1);
    unordered_set<int> seen;
    int zeros = 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            zeros++;
        } else if (1 <= a[i] && a[i] <= n) {
            seen.insert(a[i]);
        }
    }
    return {a, seen, zeros};
}

// Computes locked positions and returns interval length
int compute_locked_range(const vector<int>& a, const unordered_set<int>& seen, int zeros) {
    int n = (int)a.size() - 1;
    vector<bool> locked(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (a[i] == i) locked[i] = true;
    }

    bool special = false;
    int posZero = -1, missingVal = -1;

    if (zeros == 1) {
        for (int i = 1; i <= n; i++) if (a[i] == 0) posZero = i;
        for (int v = 1; v <= n; v++) if (!seen.count(v)) { missingVal = v; break; }
        if (posZero == missingVal) special = true;
    }

    int L = 1;
    while (L <= n && (locked[L] || (special && L == posZero))) L++;
    if (L > n) return 0;

    int R = n;
    while (R >= 1 && (locked[R] || (special && R == posZero))) R--;

    return R - L + 1;
}

// -------------------------------------------------- //

void solve_case() {
    int n;
    cin >> n;

    auto [nums, seen, zeros] = read_input(n);
    int ans = compute_locked_range(nums, seen, zeros);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_case();
    }
    return 0;
}
