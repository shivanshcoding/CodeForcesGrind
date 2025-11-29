#include <bits/stdc++.h>
using namespace std;
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
#define prDouble(x) cout<<fixed<<setprecision(10)<<x
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
// #define s second
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using tll = tuple<ll,ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

bool ispalin(const string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}

void flip_sub(string& s, int l, int r) {
    for (int i = l; i <= r; ++i) s[i] = (s[i] == '0' ? '1' : '0');
}

void solve_one() {
    if (!(cin >> n)) return;
    string s, t;
    cin >> s >> t;
    if (s == t) {
        cout << "0\n";
        return;
    }

    vector<pll> ans;
    int l = 0, r = n - 1;
    int steps = 0;

    while (l <= r) {
        if ((int)ans.size() > 2*n) { cout << "-1\n"; return; }
        if (++steps > 10000) { cout << "-1\n"; return; }

        if (s[l] == t[l]) { ++l; continue; }
        if (s[r] == t[r]) { --r; continue; }

        bool made = false;
        for (int k = l + 1; k <= r; ++k) {
            if (ispalin(s, l, k)) {
                ans.push_back({l+1, k+1});
                flip_sub(s, l, k);
                made = true;
                break;
            }
        }
        if (made) continue;

        for (int k = r - 1; k >= l; --k) {
            if (ispalin(s, k, r)) {
                ans.push_back({k+1, r+1});
                flip_sub(s, k, r);
                made = true;
                break;
            }
        }
        if (made) continue;

        if (l + 2 < n) {
            ans.push_back({l+2, l+3});
            flip_sub(s, l+1, l+2);

            ans.push_back({l+1, l+3});
            flip_sub(s, l, l+2);
            continue;
        }

        if (r - 2 >= 0) {
            ans.push_back({r-1, r});
            flip_sub(s, r-2, r-1);

            ans.push_back({r-1, r+1});
            flip_sub(s, r-2, r);
            continue;
        }
        cout << "-1\n";
        return;
    }

    if (s != t) { cout << "-1\n"; return; }
    if ((int)ans.size() > 2*n) { cout << "-1\n"; return; }
    cout << ans.size() << "\n";
    for (auto &p : ans) cout << p.f << " " << p.second << "\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve_one();
    return 0;
}
