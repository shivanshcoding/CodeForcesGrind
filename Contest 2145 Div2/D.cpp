#include <bits/stdc++.h>
using namespace std;

struct PermutationBuilder {
    int n, k;
    vector<int> binom;
    vector<vector<int>> dp;

    PermutationBuilder(int N, int K) : n(N), k(K) {
        binom.resize(n + 1);
        for (int i = 0; i <= n; ++i) binom[i] = i * (i - 1) / 2;

        int total = binom[n];
        dp.assign(n + 1, vector<int>(total + 1, 0));
        dp[0][0] = -1; // base case
    }

    void fillDP() {
        int total = binom[n];
        for (int len = 1; len <= n; ++len) {
            for (int sortedCount = 0; sortedCount <= total; ++sortedCount) {
                for (int run = 1; run <= len; ++run) {
                    int cost = binom[run];
                    if (sortedCount >= cost && dp[len - run][sortedCount - cost] != 0) {
                        dp[len][sortedCount] = run;
                        break;
                    }
                }
            }
        }
    }

    vector<int> reconstructPermutation() {
        int targetSorted = binom[n] - k;
        if (dp[n][targetSorted] == 0) return {};

        vector<int> runs;
        int remLen = n, remSorted = targetSorted;
        while (remLen > 0) {
            int runLen = dp[remLen][remSorted];
            runs.push_back(runLen);
            remLen -= runLen;
            remSorted -= binom[runLen];
        }

        reverse(runs.begin(), runs.end());
        vector<int> perm;
        int cur = 1;
        for (int runLen : runs) {
            vector<int> block;
            for (int i = 0; i < runLen; ++i) block.push_back(cur + i);
            perm.insert(perm.begin(), block.begin(), block.end());
            cur += runLen;
        }
        return perm;
    }
};

void solveCase() {
    int n, k;
    cin >> n >> k;
    PermutationBuilder builder(n, k);
    builder.fillDP();
    vector<int> perm = builder.reconstructPermutation();
    if (perm.empty()) {
        cout << 0 << '\n';
        return;
    }
    for (int x : perm) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solveCase();
    return 0;
}
