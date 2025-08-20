#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long x;
        cin >> x;
        long long t = x % 14;
        long long d = x / 14;
        if (d >= 1 && t >= 1 && t <= 6)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
