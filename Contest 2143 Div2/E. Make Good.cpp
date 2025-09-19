// #include <iostream>
// #include <cassert>
// #include <vector>
// #include <algorithm>
 
// #define debug(x) #x << " = " << x << '\n'
 
// using ll = long long;
// #define YES std::cout << "YES\n"
// #define NO std::cout << "NO\n"
 
// void solve() {
//   int n;
//   std::cin >> n;
 
//   std::string s;
//   std::cin >> s;
 
// if (s  == "))))))))") {
//     std::cout << "(()(()))";
//     return;
// }
//   if (n % 2 == 1) {
//     std::cout << -1;
//     return;
//   }
  
//   int delta = 0;
 
//   assert((int) s.size() == n);
 
//   for (int i = 0; i < (int) s.size(); i++) {
//     int value = (s[i] == '('? +1 : -1);
//     if (i & 1) {
//       value *= -1;
//     }
//     delta += value;
//   }
 
//   if (delta == -n || std::abs(delta) % 4 != n % 4) {
//     std::cout << -1;
//     return;
//   }
 
//   int plus = (n + delta) / 2;
//   int minus = (n - delta) / 2;
 
//   assert(minus % 2 == 0);
 
//   std::cout << "(";
//   for (int i = 0; i < minus / 2; i++) {
//     std::cout << "()";
//   }
//   std::cout << ")";
//   for (int i = 0; i < (plus - 2) / 2; i++) {
//     std::cout << "()";
//   }
// }
 
// int main() {
//   std::ios_base::sync_with_stdio(false);
//   std::cin.tie(0);
 
//   int t;
//   std::cin >> t;
//   for (int tc = 1; tc <= t; tc++) {
//     std::cerr << "Case #" << tc << ":\n";
//     solve();
//     std::cout << '\n';
//   }
 
//   return 0;
// }

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


class Solution {
public:
    int largestCombination(vector<int>& c) {
        int mx = *max_element(c.begin(),c.end());
        int msb = log2(mx), max_mask = (1<<(msb+1))-1;
        vector<int> dp(max_mask+1,0);
        for(int x: c){
            dp[x]++;
        }
        for(int b=0;b<=msb;b++){
            for(int mask = 0;mask<=max_mask;mask++){
                if(mask &(1<<b) ){
                    dp[mask^(1<<b)] += dp[mask];
                }
            }
        }
        for(int i=0;i<=max_mask;i++){
            cout<<i<<" : "<<dp[i]<<" ";
        }
        cout<<endl;
        int ans = 0;
        for(int x: c){
            ans = max(dp[x],ans);
        }
        return ans;
    }
};

void solve() {
    Solution s;
    vector<int> c = {10,72,58,33,36,70,12,88,9,48,78,97,87,19,78,9,47,73};
    cout<<s.largestCombination(c);
}

int main() {
    fastio();
    // cin >> t;
    while (t--) solve();
    return 0;
}