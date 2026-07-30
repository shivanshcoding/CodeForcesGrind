#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
using namespace std;
bool a[200005], b[200005];
void solve() {
    int n;
    cin >> n;
    bool pa = 0, pb = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pa ^= a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        pb ^= b[i];
    }
    if (pa == pb) {
        cout << "Tie\n";
        return;
    }
    for (int i = n; i > 0; --i) {
        if (a[i] ^ b[i]) {
            if (i & 1) {
                cout << "Ajisai\n";
            }
            else {
                cout << "Mai\n";
            }
            return;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
