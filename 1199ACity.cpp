#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // Iterate through each day
    for (int i = 0; i < n; i++) {
        bool valid = true;

        // Check previous `x` days
        for (int j = i - 1; j >= max(0, i - x); j--) {
            if (v[i] >= v[j]) {
                valid = false;
                break;
            }
        }

        // Check next `y` days
        for (int j = i + 1; j <= min(n - 1, i + y); j++) {
            if (v[i] >= v[j]) {
                valid = false;
                break;
            }
        }

        // If valid, print the result and return
        if (valid) {
            cout << i + 1 << endl;  // 1-based index
            return 0;
        }
    }
    
    return 0;
}
