#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        long long c, sum;
        cin >> c >> sum;
        long long q = sum / c;
        long long r = sum % c;
        long long cost = r * (q + 1) * (q + 1) + (c - r) * q * q;
        cout << cost << "\n";
    }
    return 0;
}
