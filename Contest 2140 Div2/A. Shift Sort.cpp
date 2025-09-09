#include <bits/stdc++.h>
using namespace std;

int solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    // Count zeros
    int count_0 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            count_0++;
        }
    }
    
    // In a sorted string, first count_0 positions should be 0
    // Count how many 1s are in the first count_0 positions
    int ones_in_zero_section = 0;
    for (int i = 0; i < min(count_0, n); i++) {
        if (s[i] == '1') {
            ones_in_zero_section++;
        }
    }
    
    return ones_in_zero_section;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int result = solve();
        cout << result << "\n";
    }
    
    return 0;
}