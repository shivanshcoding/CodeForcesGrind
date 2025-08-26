#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long x, y, a, b;
        cin >> x >> y;
        cin >> a >> b;

        b = min(b, 2 * a); // equivalent to b = min(b, a+a)
        if (x < y) swap(x, y);

        cout << y * b + (x - y) * a << "\n";
    }

    return 0;
}
