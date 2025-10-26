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
#define s second
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



void solve() {
    cin >> n >> k;

    vector<int> arr;
    vector<bool> used(n + 1, false);
    ll tk = k;
    bool poss = true;

    for (ll i = 2; i * i <= tk; ++i) {
        if (tk % i == 0) {
            ll pp = 1;
            while (tk % i == 0) {
                pp *= i;
                tk /= i;
            }
            if (pp > n) {
                poss = false;
                break;
            }
            arr.push_back((int)pp);
            used[(int)pp] = true;
        }
    }

    if (tk > 1) {
        if (tk > n) {
            poss = false;
        } else {
            arr.push_back((int)tk);
            used[(int)tk] = true;
        }
    }

    if (!poss) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    if (k == 1 && n >= 1 && !used[1]) {
         arr.push_back(1);
         used[1] = true;
    }


    // Print the subarray elements first
    for (int i = 0; i < (int)arr.size(); ++i) {
        cout << arr[i] << " ";
    }

    // Print all other unused elements from 1 to n
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}