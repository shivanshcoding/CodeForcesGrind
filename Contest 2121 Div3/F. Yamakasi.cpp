#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
int const maxn = 2e5 + 5;
int a[maxn];
ll pref[maxn], s;

main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> s >> x;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }
        ll ans = 0;
        map<ll, int> cnt;
        int lef = 1;
        for (int r = 1; r <= n; r++) {
            if (a[r] > x) cnt.clear(), lef = r + 1;
            else if (a[r] == x) {
                while (lef <= r) {
                    cnt[pref[lef - 1]]++;
                    lef++;
                }
            }
            ans += cnt[pref[r] - s];
        }
        cout << ans << '\n';
    }
    return 0;
}