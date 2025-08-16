#include <bits/stdc++.h>
using namespace std;
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,k,a,b,c,d,q,x,y,  MOD = 1e9+7;

void solve() {
    cin >> n;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a >> b >> c >> d;
        if (b > d) {
            ans += (a + b - d);
        } else if (a > c) {
            ans += (a - c);
        }
    }
    cout << ans << "\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}