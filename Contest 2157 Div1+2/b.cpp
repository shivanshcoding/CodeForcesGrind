#include <bits/stdc++.h>
using namespace std;

#define enl '\n'
#define ll long long

void $olve() {
    int n, x, y;
    cin >> n >> x >> y;
    x = abs(x), y = abs(y);
    string s;
    cin >> s;
    int opx = 0, opy = 0;
    for (auto i: s) if (i == '8')opx++, opy++;
    for (auto i: s)
    {
        if (i == '8')continue;
        if (opx < x)opx++;
        else opy++;
    }
    cout << ((opx >= x && opy >= y) || (opx >= y && opy >= x) ? "YES" : "NO") << enl;
}

void F_F() {
    cin.tie(0)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

signed main() {
    F_F();
    int T = 1;
    cin >> T;
    while (T--)$olve();
    return 0;
}
