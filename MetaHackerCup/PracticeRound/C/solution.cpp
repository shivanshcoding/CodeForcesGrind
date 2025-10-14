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

// Structure to hold the operation details
struct Operation {
    int type;
    int k;
};

void printBlocks(const std::vector<std::vector<int>>& blocks) {
    std::cout << "\nDetected Permutation Blocks (2D Array):" << std::endl;
    for (const auto& block : blocks) {
        std::cout << "[ ";
        for (int val : block) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> blocks;
    int limit = 0, st = 0;
    vector<int> cur;
    for(int i=0;i<n;i++){
        if(i==limit+1 && !(a[st]==1 && a[i]==a[i-1]+1)){
            blocks.push_back(cur);
            cur.clear();
            st = i;
        }
        limit = max(limit,a[i]+st-1);
        cur.push_back(a[i]);
    }
    blocks.push_back(cur);
    // --- Start of Corrected Block ---
    
    reverse(all(blocks));
    // --- End of Corrected Block ---

    vector<Operation> reverse_ops;
    long long total_rotations_applied_to_later_blocks = 0;

    // Process blocks from last-added to first-added to determine operations
    for (const auto& block : blocks) {
        int k = block.size();
        if (k == 0) continue;

        // The number of total left rotations 'r' is determined by the first element.
        // An identity permutation [1, 2, ...] becomes [r+1, ...] after 'r' rotations.
        int total_rots_for_this_block = block[0] - 1;
        
        // Calculate rotations applied specifically between this block's creation and the next
        long long needed_rots = (total_rots_for_this_block - (total_rotations_applied_to_later_blocks % k) + k) % k;

        for (int i = 0; i < needed_rots; ++i) {
            reverse_ops.push_back({2, 0});
        }
        total_rotations_applied_to_later_blocks += needed_rots;

        reverse_ops.push_back({1, k});
    }
    // The operations were determined in reverse order, so flip the list
    reverse(reverse_ops.begin(), reverse_ops.end());

    cout << reverse_ops.size() << "\n";
    for (const auto& op : reverse_ops) {
        if (op.type == 1) {
            cout << "1 " << op.k << "\n";
        } else {
            cout << "2\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}