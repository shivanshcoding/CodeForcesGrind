#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }

        int ans = 0;
        
        // Count 'D' in last row (except last cell)
        for (int j = 0; j < m - 1; j++) {
            if (grid[n - 1][j] == 'D') ans++;
        }

        // Count 'R' in last column (except last cell)
        for (int i = 0; i < n - 1; i++) {
            if (grid[i][m - 1] == 'R') ans++;
        }

        cout << ans << "\n";
    }
    return 0;
}
