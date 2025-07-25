#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    cout << "2\n"; // The minimum final number is always 2 for n >= 2
    int a = n, b = n - 1;

    for (int i = n - 1; i > 1; --i) {
        cout << a << " " << b << "\n";
        a = (a + b + 1) / 2; // Equivalent to ceil((a + b) / 2)
        b = i - 1;
    }
    cout << a << " " << b << "\n"; // Final merge step
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}