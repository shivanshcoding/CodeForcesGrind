#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int a, b, x, y;
        std::cin >> a >> b >> x >> y;

        if (a > b) {
            if ((a ^ 1) == b) {
                std::cout << y << '\n';
            } else {
                std::cout << -1 << '\n';
            }
        } else {
            int c0 = b - a;
            int c1 = ((b + 1) >> 1) - ((a + 1) >> 1);

            long long ans = (y > x)
                ? 1LL * c0 * x
                : 1LL * (c0 - c1) * x + 1LL * c1 * y;

            std::cout << ans << '\n';
        }
    }
}
