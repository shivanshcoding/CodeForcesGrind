// #include <bits/stdc++.h>
// using namespace std;
// struct custom_hash {
//    static uint64_t splitmix64(uint64_t x) {
//        x += 0x9e3779b97f4a7c15;
//        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//        return x ^ (x >> 31);
//    }
// size_t operator()(uint64_t x) const {
//        static const uint64_t FIXED_RANDOM =
//        chrono::steady_clock::now().time_since_epoch().count();
//        return splitmix64(x + FIXED_RANDOM);
//    }
// };
// #define prDouble(x) cout<<fixed<<setprecision(10)<<x
// #define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()
// #define pb push_back
// #define f first
// #define sz(x) (int)(x).size()
// using ll = long long;
// using ld = long double;
// using pll = pair<ll,ll>;
// using tll = tuple<ll,ll,ll>;
// using vll = vector<ll>;
// using vpll = vector<pll>;
// vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
// vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
// template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
// template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
// template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
// ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
// const ll INF = 1e18, MOD = 1e9+7;

// void solve() {
//     cin>>n>>q;
//     vector<ll> p(n), s(n);
//     read(p);
//     read(s);
//     while(q--){

//     }
// }

// int main() {
//     fastio();
//     cin >> t;
//     while (t--) solve();
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> p(n+1), s(n+1);        // 1-based indexing
        vector<int> rank_p(n+1), rank_s(n+1);
        vector<int> combined_rank(n+1);

        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            rank_p[p[i]] = i;               // store position of item
        }

        for (int i = 1; i <= n; i++) {
            cin >> s[i];
            rank_s[s[i]] = i;               // store position of item
        }

        long long total_pairs = 0;
        for (int i = 1; i <= n; i++) {
            combined_rank[i] = max(rank_p[i], rank_s[i]);
            total_pairs += combined_rank[i];
        }

        while (q--) {
            int tp, x, y;
            cin >> tp >> x >> y;

            if (tp == 1) {
                // Swap in p
                swap(p[x], p[y]);
                rank_p[p[x]] = x;
                rank_p[p[y]] = y;
            } else {
                // Swap in s
                swap(s[x], s[y]);
                rank_s[s[x]] = x;
                rank_s[s[y]] = y;
            }

            // Update combined ranks of the two swapped items
            for (int item : {p[x], p[y], s[x], s[y]}) {
                long long old_cr = combined_rank[item];
                combined_rank[item] = max(rank_p[item], rank_s[item]);
                total_pairs += combined_rank[item] - old_cr;
            }

            cout << total_pairs << "\n";
        }
    }

    return 0;
}
