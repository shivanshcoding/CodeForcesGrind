#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> h(n);
        for (int i = 0; i < n; i++) cin >> h[i];

        vector<long long> dp(n + 1, 0);
        dp[1] = h[0];

        for (int i = 1; i < n; i++) {
            dp[i + 1] = min(dp[i] + h[i] - 1,
                            dp[i - 1] + h[i - 1] + max(0LL, h[i] - i));
        }

        cout << dp[n] << "\n";
    }
    return 0;
}
