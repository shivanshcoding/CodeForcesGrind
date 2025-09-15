#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ---------------- Helper Functions ---------------- //

// Reads array and returns max element
pair<vector<int>, int> read_array(int n) {
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    return {a, mx};
}

// Build frequency map and prefix sum
vector<int> build_prefix(const vector<int>& a, int mx) {
    vector<int> freq(mx + 1, 0);
    for (int x : a) freq[x]++;
    vector<int> pref(mx + 1);
    partial_sum(freq.begin(), freq.end(), pref.begin());
    return pref;
}

// Evaluate score for a given step
ll evaluate_step(int step, int n, int mx, const vector<int>& pref, const vector<int>& freq, ll Y) {
    int blocks = (mx + step - 1) / step;
    ll score = 0, fix = 0;

    for (int blk = 1; blk <= blocks; blk++) {
        int L = (blk - 1) * step + 1;
        int R = min(blk * step, mx);
        if (L > R) continue;

        int seg = pref[R] - pref[L - 1];
        if (seg == 0) continue;

        score += 1LL * blk * seg;
        if (blk <= mx) fix += min(seg, freq[blk]);
    }

    ll miss = n - fix;
    return score - Y * miss;
}

// Main case solver
void solve_case() {
    int n;
    ll Y;
    cin >> n >> Y;

    auto [arr, mx] = read_array(n);
    vector<int> freq(mx + 1, 0);
    for (int x : arr) freq[x]++;

    vector<int> pref(mx + 1);
    partial_sum(freq.begin(), freq.end(), pref.begin());

    ll best = LLONG_MIN;
    for (int step = 2; step <= mx + 1; step++) {
        best = max(best, evaluate_step(step, n, mx, pref, freq, Y));
    }

    cout << best << "\n";
}

// -------------------------------------------------- //

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve_case();

    return 0;
}
