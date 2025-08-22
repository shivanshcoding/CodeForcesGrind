#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        long long x, y;
        cin >> x >> y;
        bool ok = false;
        if (x >= y) ok = true;
        else if (x == 1) ok = (y == 1);
        else if (x == 2) ok = (y <= 3);
        else if (x == 3) ok = (y <= 3);
        else ok = true; // x >= 4
        cout << (ok ? "YES\n" : "NO\n");
    }
}
