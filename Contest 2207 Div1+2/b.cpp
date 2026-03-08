#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, m;
    long long l;
    cin >> n >> m >> l;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // dp[k] represents the max possible sum of the top k animatronics
    vector<long long> dp(m + 1, 0);
    long long last_time = 0;
    
    for (int i = 0; i < n; i++) {
        long long L = a[i] - last_time;
        
        // Time passes: the adversary adds L to the top k sum capabilities
        for (int k = 1; k <= m; k++) {
            dp[k] += L;
        }
        
        // Player flashes: resets the highest element to 0
        vector<long long> next_dp(m + 1, 0);
        for (int k = 1; k < m; k++) {
            next_dp[k] = (1LL * k * dp[k + 1]) / (k + 1);
        }
        // Element m bound caps off at m-1 because 1 element was zeroed out
        next_dp[m] = next_dp[m - 1]; 
        
        dp = next_dp;
        last_time = a[i];
    }
    
    // Remaining time until the end of the night
    long long L = l - last_time;
    for (int k = 1; k <= m; k++) {
        dp[k] += L;
    }
    
    // The maximum individual danger level possible at the end of the night
    cout << dp[1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}