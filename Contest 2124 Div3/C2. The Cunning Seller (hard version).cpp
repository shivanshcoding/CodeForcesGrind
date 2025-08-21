#include <bits/stdc++.h>
using namespace std;
#define tej ios::sync_with_stdio(false); cin.tie(nullptr)
#define sab(x) (x).begin(), (x).end()
#define pb push_back
using ll = long long;
using ull = unsigned long long;

// -------- utility: base-3 digit sum ----------
ll base3_digit_sum(ll x) {
    ll ans = 0;
    while (x > 0) {
        ans += x % 3;
        x /= 3;
    }
    return ans;
}

void hal_kar() {
    ll n, k;
    cin >> n >> k;

    ll min_moves = base3_digit_sum(n);

    // effective moves cannot exceed n
    ll moves = min(n, k);

    // parity adjust
    if (((n - moves) & 1LL) == 1) moves--;

    if (moves < min_moves) {
        cout << -1 << "\n";
        return;
    }

    // remaining "lifts" we must perform
    ll remaining = (n - moves) / 2;

    // use max-heap to simulate splitting
    priority_queue<pair<int, ull>> pq;
    pq.push({0, (ull)n}); // {power-of-3 level, count}

    ull extra = 0;

    while (remaining > 0 && !pq.empty()) {
        auto [level, cnt] = pq.top(); pq.pop();

        if (cnt < 3) continue;

        ull can_take = cnt / 3;
        ull take = min<ull>(can_take, (ull)remaining);

        extra += take * (ull)pow(3, level); 
        remaining -= take;

        // leftover at same level
        ull left = cnt - take * 3;
        if (left > 0) pq.push({level, left});

        // promote taken ones to next level
        pq.push({level + 1, take});
    }

    ull ans = 3ull * (ull)n + extra;
    cout << ans << "\n";
}

int main() {
    tej;
    int t; 
    cin >> t;
    while (t--) hal_kar();
    return 0;
}
