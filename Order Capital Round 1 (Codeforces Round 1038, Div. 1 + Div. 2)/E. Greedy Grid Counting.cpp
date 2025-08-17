#include <bits/stdc++.h>
using namespace std;
const long long M = 998244353LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        vector<long long> d(k + 1), p(k + 1), q(k + 1);
        vector<long long> d1(n + 1);
        d1[0] = 1;

        for (int i = 1; i <= n - 1; i++) {
            p[0] = d[0] % M;
            q[0] = (d[0] * (k + 1LL)) % M;
            for (int j = 1; j <= k; j++) {
                p[j] = (p[j - 1] + d[j]) % M;
                long long add = (d[j] * ((k + 1LL) - j)) % M;
                q[j] = (q[j - 1] + add) % M;
            }

            if (a[i + 1] == -1 && b[i] == -1) {
                vector<long long> nd(k + 1);
                for (int j = 0; j <= k; j++) {
                    long long v;
                    if (j == 0) {
                        v = (q[k] - p[k]) % M;
                        if (v < 0) v += M;
                    } else {
                        long long v1 = (q[k] - q[j - 1]) % M;
                        if (v1 < 0) v1 += M;
                        long long v2 = (p[k] - p[j - 1]) % M;
                        if (v2 < 0) v2 += M;
                        v = (v1 + v2 * (j - 1)) % M;
                    }
                    if (j != 0) {
                        long long ex = (p[k] * (k - j)) % M;
                        ex = (ex + d1[i - 1] * (k - j)) % M;
                        v = (v + ex) % M;
                    }
                    nd[j] = v;
                }
                d = nd;
                long long t = ((1LL * k * k) - (1LL * k * (k - 1) / 2LL)) % M;
                if (t < 0) t += M;
                d1[i] = (d1[i - 1] * t) % M;
                continue;
            }

            int l = ((a[i + 1] == -1 ? 1 : a[i + 1]) - (b[i] == -1 ? k : b[i]));
            int r = ((a[i + 1] == -1 ? k : a[i + 1]) - (b[i] == -1 ? 1 : b[i]));

            vector<long long> nd(k + 1);
            for (int j = 0; j <= k; j++) {
                int l2 = max(j + l, j) - 1;
                int r2 = min(k, j + r);
                long long v = 0;
                if (l2 < r2) {
                    long long v1 = (r2 >= 0 ? p[r2] : 0);
                    long long v2 = (l2 >= 0 ? p[l2] : 0);
                    v = (v1 - v2) % M;
                    if (v < 0) v += M;
                }
                if (-r <= j && j <= -l && j != 0) {
                    v = (v + d1[i - 1] + p[k]) % M;
                }
                nd[j] = v;
            }
            d = nd;
            int c = max(0, (r + 1) - max(l, 0));
            d1[i] = (d1[i - 1] * (c % M)) % M;
        }

        long long ans = d1[n - 1];
        for (int j = 0; j <= k; j++) ans = (ans + d[j]) % M;
        if (a[1] == -1) ans = (ans * k) % M;
        if (b[n] == -1) ans = (ans * k) % M;
        cout << (ans % M + M) % M << "\n";

        // reset d
        fill(d.begin(), d.end(), 0);
    }

    return 0;
}
