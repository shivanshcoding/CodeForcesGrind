#include <bits/stdc++.h>
using namespace std;

bool check(long long r, long long g, long long b, long long w) {
    int odd = (r % 2) + (g % 2) + (b % 2) + (w % 2);
    return odd <= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long r, g, b, w;
        cin >> r >> g >> b >> w;

        bool ok = false;
        // Case 1: without any operation
        if (check(r, g, b, w)) ok = true;
        // Case 2: try one operation if possible
        else if (r > 0 && g > 0 && b > 0) {
            if (check(r - 1, g - 1, b - 1, w + 3)) ok = true;
        }

        cout << (ok ? "Yes\n" : "No\n");
    }
    return 0;
}
