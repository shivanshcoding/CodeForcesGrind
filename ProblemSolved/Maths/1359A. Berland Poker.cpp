#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;

        int ans = 0;
        int d = n / k;

        for (int a1 = 0; a1 <= m; a1++) {
            for (int a2 = 0; a2 <= a1; a2++) {
                if (a1 > d) continue;
                if (a1 + a2 > m) continue;
                if (a1 + (k - 1) * a2 < m) continue;

                ans = max(ans, a1 - a2);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
