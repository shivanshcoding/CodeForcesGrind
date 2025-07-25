#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll nb, ns, nc, pb, ps, pc, r;
ll cb = 0, cs = 0, cc = 0;  // Ingredients required per hamburger

bool canMake(ll x) {
    ll neededB = max(0LL, x * cb - nb);
    ll neededS = max(0LL, x * cs - ns);
    ll neededC = max(0LL, x * cc - nc);

    ll cost = neededB * pb + neededS * ps + neededC * pc;
    return cost <= r;
}

int main() {
    string recipe;
    cin >> recipe;
    
    for (char c : recipe) {
        if (c == 'B') cb++;
        else if (c == 'S') cs++;
        else if (c == 'C') cc++;
    }

    cin >> nb >> ns >> nc;
    cin >> pb >> ps >> pc;
    cin >> r;

    ll low = 0, high = 1e13, ans = 0;
    
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (canMake(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans << endl;
    return 0;
}
