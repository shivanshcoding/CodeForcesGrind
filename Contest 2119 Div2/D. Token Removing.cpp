#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5005;

inline void add(int& x, int y, int mod) {
    x += y;
    if (x >= mod) x -= mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, mod;
        cin >> n >> mod;

        static int f[N][N];
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                f[i][j] = 0;

        f[0][0] = 1;
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                int now = f[i - 1][j];
                if (!now) continue;

                add(f[i][j + 1], now, mod);
                f[i][j] = (f[i][j] + 1LL * (n - i + 1) * (j + 1) % mod * now) % mod;
            }
        }

        for (int j = 0; j <= n; j++) add(ans, f[n][j], mod);

        cout << ans << "\n";
    }
}
