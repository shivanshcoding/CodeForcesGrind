#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while (tt--) {
        ll n, k;
        cin >> n >> k;
        unordered_map<ll, int, custom_hash> cnt;
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            ll r = x % k;
            cnt[min(r, k-r)]++;
        }
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            ll r = x % k;
            cnt[min(r, k-r)]--;
        }
        bool ok = true;
        for (auto &p : cnt) {
            if (p.second != 0) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
