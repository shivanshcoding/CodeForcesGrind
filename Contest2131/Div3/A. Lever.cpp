#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(), (x).end();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int ans= 0;
        for(int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                ans += a[i]-b[i];
            }
        }
        cout << ans +1<< endl;
    }
    return 0;
}
