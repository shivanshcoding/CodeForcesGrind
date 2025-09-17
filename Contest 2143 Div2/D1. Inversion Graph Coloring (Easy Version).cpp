#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
int n;
int a[305];
int dp[305][305][305]; // dp[i][x][y]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];

        // dp[pos][lastX][lastY] = number of ways
        // lastX = last element in subseq X, lastY = last element in subseq Y
        // compressed by indexing with values in [0..n]
        static int dp[305][305][305];
        for (int i=0;i<=n;i++)
            for (int j=0;j<=n;j++)
                for (int k=0;k<=n;k++)
                    dp[i][j][k] = 0;

        dp[0][0][0] = 1; // start empty (both subsequences empty)

        for (int i = 1; i <= n; i++) {
            for (int x = 0; x <= n; x++) {
                for (int y = 0; y <= n; y++) {
                    int val = dp[i-1][x][y];
                    if (!val) continue;

                    // Option 1: skip a[i]
                    dp[i][x][y] = (dp[i][x][y] + val) % MOD;

                    // Option 2: put in subsequence X
                    if (x <= a[i])
                        dp[i][a[i]][y] = (dp[i][a[i]][y] + val) % MOD;

                    // Option 3: put in subsequence Y
                    if (y <= a[i])
                        dp[i][x][a[i]] = (dp[i][x][a[i]] + val) % MOD;
                }
            }
        }

        long long ans = 0;
        for (int x = 0; x <= n; x++) {
            for (int y = 0; y <= n; y++) {
                ans = (ans + dp[n][x][y]) % MOD;
            }
        }

        cout << ans % MOD << "\n";
    }
}
