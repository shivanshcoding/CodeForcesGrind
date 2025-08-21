#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long w, h;
        cin >> w >> h;

        long long ans = 0;

        // bottom side
        int k;
        cin >> k;
        vector<long long> x1(k);
        for (int i = 0; i < k; i++) cin >> x1[i];
        ans = max(ans, (x1.back() - x1.front()) * h);

        // top side
        cin >> k;
        vector<long long> x2(k);
        for (int i = 0; i < k; i++) cin >> x2[i];
        ans = max(ans, (x2.back() - x2.front()) * h);

        // left side
        cin >> k;
        vector<long long> y1(k);
        for (int i = 0; i < k; i++) cin >> y1[i];
        ans = max(ans, (y1.back() - y1.front()) * w);

        // right side
        cin >> k;
        vector<long long> y2(k);
        for (int i = 0; i < k; i++) cin >> y2[i];
        ans = max(ans, (y2.back() - y2.front()) * w);

        cout << ans << "\n";
    }
    return 0;
}
