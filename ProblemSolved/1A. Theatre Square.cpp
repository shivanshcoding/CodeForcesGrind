#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m, a;
    if (!(cin >> n >> m >> a)) return 0;
    long long tiles_n = (n + a - 1) / a; // ceil(n/a)
    long long tiles_m = (m + a - 1) / a; // ceil(m/a)
    cout << tiles_n * tiles_m << '\n';
    return 0;
}
