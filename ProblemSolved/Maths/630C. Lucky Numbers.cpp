#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)

ll poww(ll base, ll exp) {
    ll ans = 1;
    while (exp > 0) {
        if (exp & 1) ans = ans * base;
        base = base * base;
        exp >>= 1;
    }
    return ans;
}

int main() {
    fastio();
    ll n;
    if (!(cin >> n)) return 0;
    // sum 2^1 + 2^2 + ... + 2^n = 2^(n+1) - 2
    cout << (poww(2, n+1) - 2) << '\n';
    return 0;
}
