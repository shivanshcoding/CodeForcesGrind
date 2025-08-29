#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Function to compute (min digit * max digit)
ll getAdd(ll x) {
    ll mn = 10, mx = 0;
    while (x > 0) {
        ll d = x % 10;
        x /= 10;
        mn = min(mn, d);
        mx = max(mx, d);
    }
    return mn * mx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll x, k;
        cin >> x >> k;
        --k;
        while (k--) {
            ll y = getAdd(x);
            if (y == 0) break;
            x += y;
        }
        cout << x << "\n";
    }
    return 0;
}
