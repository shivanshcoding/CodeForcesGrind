#include <bits/stdc++.h>
using namespace std;

void processTestcase() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> intervals(m);
    int L = 1, R = n;

    for (auto &it : intervals) {
        cin >> it.first >> it.second;
        L = max(L, it.first);
        R = min(R, it.second);
    }

    vector<int> perm(n, -1);

    if (L <= R) {
        // Simple case: intersection exists
        int anchor = L - 1;
        perm[anchor] = 0;
        int label = 1;
        for (int i = 0; i < n; ++i)
            if (perm[i] == -1) perm[i] = label++;
    } 
    else {
        // Complex case: need to pick two suitable positions
        bool solved = false;

        for (int i = 1; i <= n && !solved; ++i) {
            int coverCount = 0, left = 1, right = n;

            for (auto [l, r] : intervals) {
                if (l <= i && i <= r) {
                    coverCount++;
                    left = max(left, l);
                    right = min(right, r);
                }
            }

            if (coverCount == 0) {
                int idx0 = i - 1;
                int idx1 = i % n;
                perm[idx0] = 0;
                perm[idx1] = 1;
                int val = 2;
                for (int j = 0; j < n; ++j)
                    if (perm[j] == -1) perm[j] = val++;
                solved = true;
            } 
            else if (right - left + 1 >= 2) {
                int idx0 = i - 1;
                int b = (i != left) ? left : left + 1;
                int idx1 = b - 1;
                perm[idx0] = 0;
                perm[idx1] = 1;
                int val = 2;
                for (int j = 0; j < n; ++j)
                    if (perm[j] == -1) perm[j] = val++;
                solved = true;
            }
        }

        if (!solved) {
            // fallback pattern
            perm[0] = 0;
            perm[2 % n] = 1;
            perm[1] = 2;
            int v = 3;
            for (int i = 0; i < n; ++i)
                if (perm[i] == -1) perm[i] = v++;
        }
    }

    for (int i = 0; i < n; ++i)
        cout << perm[i] << (i + 1 == n ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        processTestcase();
        if (t) cout.flush();
    }

    return 0;
}
