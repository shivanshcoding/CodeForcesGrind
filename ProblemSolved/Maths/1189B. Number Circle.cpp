#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    if (a[n-1] >= a[n-2] + a[n-3]) {
        cout << "NO\n";
    } else {
        cout << "YES\n";

        // print from the back, skipping one each time
        for (int i = n-1; i >= 0; i -= 2) {
            cout << a[i] << " ";
        }
        // then print from front depending on parity
        for (int i = n%2; i < n; i += 2) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
