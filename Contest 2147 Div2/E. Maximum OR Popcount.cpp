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
// #define s second
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
//     vector<ll> a(n);
//     read(a);
//     vector<ll> bit(32,0);
//     for(int i=0;i<n;i++){
//         ll dummy = a[i];
//         int count = 0;
//         while(dummy>0){
//             bit[count] += (dummy&1);
//             dummy = dummy>>1;
//             count++;
//         }
//     }
//     sort(all(a));
//     while(q--){
//         cin>>b;
//         for(int i=0;i<32;i++){
//             if(bit[i]==0){
//                 ll mask = 1<<i;
//                 auto it = lower_bound(all(a),mask);
//                 if(it!=a.begin()){
//                     it--;
//                     ll curr = *it;
                    
//                     int bt = 0;
//                     ll dum = curr;
//                     while(bt<i){
//                         if(curr&(1<<bt)){
//                             if(bit[bt]==1){
//                                 mask = mask^(1<<bt);
//                             }else{
//                                 bit[bt]--;
//                             }
//                         }
//                         bt++;
//                     }
//                     ll req = mask-curr;
//                     if(b >= mask-curr) b -= (mask-curr);
//                     else break;
//                     *it = mask;
//                 }
//             }
//             cout<<
//         }
//         cout<<"\n";
//     }
// }

// int main() {
//     fastio();
//     cin >> t;
//     while (t--) solve();
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, q;
        cin >> n >> q;
        
        vector<unsigned> a(n);
        unsigned baseOR = 0;
        unsigned min_val = UINT_MAX;
        unsigned max_val = 0;
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            baseOR |= a[i];
            min_val = min(min_val, a[i]);
            max_val = max(max_val, a[i]);
        }
        
        // Use boolean array instead of set for O(1) lookup
        bool unset_bits[32];
        for (int i = 0; i < 32; i++) {
            unset_bits[i] = !(baseOR & (1U << i));
        }
        
        int base_pop = __builtin_popcount(baseOR);
        
        // Check if all bits are set in baseOR
        bool all_set = true;
        for (int i = 0; i < 32; i++) {
            if (unset_bits[i]) {
                all_set = false;
                break;
            }
        }
        
        while (q--) {
            unsigned b;
            cin >> b;
            
            if (all_set) {
                cout << base_pop << '\n';
                continue;
            }
            
            unsigned R = max_val + b;
            
            // Use 2D DP array with better initialization
            int dp[2][2];
            int new_dp[2][2];
            
            // Initialize for bit 31
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    dp[i][j] = -1;
                }
            }
            dp[1][1] = 0;
            
            for (int bit = 31; bit >= 0; bit--) {
                int l_bit = (min_val >> bit) & 1;
                int r_bit = (R >> bit) & 1;
                
                // Clear new_dp
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        new_dp[i][j] = -1;
                    }
                }
                
                for (int tight_l = 0; tight_l < 2; tight_l++) {
                    for (int tight_r = 0; tight_r < 2; tight_r++) {
                        if (dp[tight_l][tight_r] == -1) continue;
                        
                        int low = tight_l ? l_bit : 0;
                        int high = tight_r ? r_bit : 1;
                        
                        for (int d = low; d <= high; d++) {
                            int new_tight_l = tight_l && (d == l_bit);
                            int new_tight_r = tight_r && (d == r_bit);
                            
                            // O(1) bit check instead of set::find()
                            int add = (d == 1 && unset_bits[bit]) ? 1 : 0;
                            int new_count = dp[tight_l][tight_r] + add;
                            
                            if (new_count > new_dp[new_tight_l][new_tight_r]) {
                                new_dp[new_tight_l][new_tight_r] = new_count;
                            }
                        }
                    }
                }
                
                // Copy new_dp to dp
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        dp[i][j] = new_dp[i][j];
                    }
                }
            }
            
            int ans = 0;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    ans = max(ans, dp[i][j]);
                }
            }
            
            cout << base_pop + ans << '\n';
        }
    }
    return 0;
}