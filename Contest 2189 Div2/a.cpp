#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n, h, l;
        cin >> n >> h >> l;

        long long rowOnly = 0;
        long long colOnly = 0;
        long long both = 0;

        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;

            bool row = (1 <= x && x <= h);
            bool col = (1 <= x && x <= l);

            if (row && col)
                both++;
            else if (row)
                rowOnly++;
            else if (col)
                colOnly++;
        }

        long long ans = min({rowOnly + both,
                             colOnly + both,
                             (rowOnly + colOnly + both) / 2});

        cout << ans << '\n';
    }

    return 0;
}