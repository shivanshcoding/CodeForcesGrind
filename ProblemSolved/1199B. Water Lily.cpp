#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double H, L;
    cin >> H >> L;
    double depth = (L*L - H*H) / (2.0 * H);
    cout << fixed << setprecision(12) << depth << "\n";
    return 0;
}
