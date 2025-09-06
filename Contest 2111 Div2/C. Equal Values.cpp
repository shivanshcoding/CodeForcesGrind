#include <iostream>
#include <vector>
#include <algorithm>

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long ans = -1;

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && a[j] == a[i]) {
            j++;
        }

        long long current_val = (long long)(i + n - j) * a[i];
        
        if (ans == -1 || current_val < ans) {
            ans = current_val;
        }

        i = j;
    }
    
    std::cout << ans << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
