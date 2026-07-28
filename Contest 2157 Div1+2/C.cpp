#include<bits/stdc++.h>
#define int long long
#define void inline void
using namespace std;
const int maxn = 105;
int T, n, k, qq, btot;
int c[maxn], a[maxn], d1[maxn], d2[maxn];
void GOGOGO() {
    memset(d1, 0, sizeof(d1));
    memset(d2, 0, sizeof(d2));
    cin >> n >> k >> qq;
    for (int i = 1; i <= qq; i++) {
        int l, r;
        cin >> c[i] >> l >> r;
        if (c[i] == 1) {
            d1[l]++;
            d1[r + 1]--;
        } else {
            d2[l]++;
            d2[r + 1]--;
        }
    }
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        d1[i] += d1[i - 1];
        d2[i] += d2[i - 1];
        if (d1[i]) {
            if (d2[i]) a[i] = k + 1;
            else a[i] = k;
        }
        else {
            a[i] = cur;
            cur = (cur + 1) % k;
        }
        cout << a[i] << ' ';
    }
    cout << '\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) GOGOGO();
    return 0;
}
