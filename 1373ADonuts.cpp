#include <bits/stdc++.h>
using namespace std;

int Solve1(long long a, long long b, long long c) {
    return (a < c) ? 1 : -1;
}

int Solve2(long long a, long long b, long long c) {
    return (a * b > c) ? b : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        long long a, b, c;
        cin >> a >> b >> c;
        cout << Solve1(a, b, c) << " " << Solve2(a, b, c) << endl;
    }

    return 0;
}
