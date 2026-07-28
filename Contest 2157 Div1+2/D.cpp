#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        ll l, r;
        cin >> n >> l >> r;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());
        vector<ll> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
        ll total = pref[n];
        ll ans = 0;
        for (int B = -n; B <= n; ++B) {
            // maximum number of offers we take (Left or Right)
            int k = ((n - B) % 2 == 0) ? n : n - 1;
            int x = (k - B) / 2;  // number of "p <= a_i" offers
            int y = (k + B) / 2;  // number of "p >= a_i" offers
            // best possible A for this B
            ll A = total - pref[n - x] - pref[y];
            // guaranteed score for this B
            ll score;
            if (B > 0) score = A + B * l;
            else if (B < 0) score = A + B * r;
            else score = A;
            if (score > ans) ans = score;
        }
        cout << ans << '\n';
    }
    return 0;
}
const int _cf_submit_id = 2585;