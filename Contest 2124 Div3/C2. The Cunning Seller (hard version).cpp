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
using vll = vector<ll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,k,a,b,q,x,y,z, MOD = 1e9+7;
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
    vector <long long> cost;
    long long c = 3;
    long long cnt = 1;
    for (int i = 0; i < 21; ++i) {
        cost.push_back(c);
        c = 3 * c + cnt;
        cnt *= 3;
    }

    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        vector <long long> tr;
        long long min_k = 0;
        while (n) {
            tr.push_back(n % 3);
            min_k += n % 3;
            n /= 3;
        }
        if (min_k > k) {
            cout << -1 << '\n';
            continue;
        }
        printv(tr);
        cout<<endl;
        // k -= min_k;
        // k /= 2;
        // for (int i = (int)tr.size() - 1; i >= 1; --i) {
        //     if (tr[i] <= k) {
        //         tr[i - 1] += 3 * tr[i];
        //         k -= tr[i];
        //         tr[i] = 0;
        //     } else {
        //         tr[i - 1] += k * 3;
        //         tr[i] -= k;
        //         break;
        //     }
        // }
        k -= min_k;
        for(int i=(int)tr.size()-1;i>=1;--i){
            
        }
        printv(tr);
        ll an = 0;
        for (int i = (int)tr.size() - 1; i >= 0; --i)
            an += cost[i] * tr[i];
        cout << an << '\n';
    }
    
    return 0;
}