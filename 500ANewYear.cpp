#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, t;
    cin >> n >> t;
    
    vector<int> arr(n + 1); // Adjust size to `n+1` for 1-based indexing
    for (int i = 1; i < n; i++) {
        cin >> arr[i];
    }

    int i = 1;
    while (i < t) {  // Only loop while `i < t`, avoiding unnecessary jumps
        i += arr[i];
    }
    cout << (i == t ? "YES" : "NO");  // If exactly `t` is reached, return "YES"
    return 0;
}
