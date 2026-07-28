#include <bits/stdc++.h>
using namespace std;

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());

        vector<int> b0(n);
        for (int i = 0; i < n; ++i) b0[i] = a[i] - i;

        // Returns true if after t operations max frequency <= k.
        auto check = [&](int t) -> bool {
            int w = t + 1;               // window size
            deque<int> dq;
            bool first = true;
            int prev = 0, cnt = 0;

            for (int i = 0; i < n; ++i) {
                // maintain decreasing deque of indices (max at front)
                while (!dq.empty() && b0[dq.back()] <= b0[i]) dq.pop_back();
                dq.push_back(i);
                if (dq.front() <= i - w) dq.pop_front();

                int bi = b0[dq.front()];
                int val = bi + i;        // a_i after t steps

                if (first) {
                    prev = val;
                    cnt = 1;
                    first = false;
                } else {
                    if (val == prev) {
                        cnt++;
                        if (cnt > k) return false;   // early exit
                    } else {
                        cnt = 1;
                    }
                    prev = val;
                }
            }
            return true;
        };

        // binary search for the smallest t (0 <= t <= n)
        int low = 0, high = n + 1;   // answer is at most n-1, n+1 is safe
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(mid))
                high = mid;
            else
                low = mid + 1;
        }
        cout << low << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
const int _cf_submit_id = 2485;