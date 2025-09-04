#include <bits/stdc++.h>
using namespace std;

string solve() {
    long long w, h, a, b;
    cin >> w >> h >> a >> b;
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if (x1 == x2) {
        if (abs(y1 - y2) % b == 0) return "Yes";
        else return "No";
    }

    if (y1 == y2) {
        if (abs(x1 - x2) % a == 0) return "Yes";
        else return "No";
    }

    if ((x1 - x2) % a == 0 || (y1 - y2) % b == 0) return "Yes";
    return "No";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << solve() << "\n";
    }
    return 0;
}
