#include <iostream>
#include <vector>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> ans(n);
        ans[n-1] = 1;
        for (int i = 1; i < n - 1; i++) {
            ans[i] = (i+1) ^ 1;
        }
        if (n % 2 == 0) {
            ans[0] = n;
        }
        else {
            ans[0] = n-1;
        }
        for (int i = 0; i < n; i++) std::cout << ans[i] << " ";
        std::cout << '\n';
    }
}