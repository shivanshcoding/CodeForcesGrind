#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9+7;
typedef long long ll;

// Remove the i-th bit from a bitset (bitmask)
unsigned removeBitFromMask(unsigned mask, int pos) {
    unsigned lower = mask & ((1u << (pos-1)) - 1);
    unsigned upper = mask >> pos;
    return lower | (upper << (pos-1));
}

// Fast integer exponentiation modulo MOD
int modExp(ll base, ll exp) {
    ll result = 1;
    while(exp > 0) {
        if(exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return static_cast<int>(result);
}

// Solve a single test case
void solveCase() {
    int n, m, k;
    cin >> n >> m >> k;

    // store allowed moves in unordered_set for O(1) lookup
    unordered_set<int> allowed;
    for(int i=0; i<k; ++i){
        int mv; cin >> mv;
        allowed.insert(mv);
    }

    if(m == 1){ cout << 1 << "\n"; return; }

    // Map pile size -> allowed moves (vector)
    map<int, deque<int>> movesForPile;
    for(int pile=1; pile<=n; ++pile){
        for(int mv : allowed){
            if(mv <= pile) movesForPile[pile].push_back(mv);
        }
    }

    // DP: store previous pile states using bitset
    bitset<1024> prevDP; // max pile size <= 10
    prevDP.set(1); // initial state
    prevDP.reset(0);

    for(int pile=2; pile<=n; ++pile){
        int maskSize = 1 << pile;

        // current DP state using unordered_map instead of vector
        unordered_map<unsigned, bool> currDP;

        bool isAliceTurn = ((n - pile) % 2 == 0);

        auto &moves = movesForPile[pile];

        // Iterate masks using iterator
        for(int mask=0; mask<maskSize; ++mask){
            if(isAliceTurn){
                bool winFlag = false;
                for(auto it = moves.begin(); it != moves.end(); ++it){
                    if(prevDP[removeBitFromMask(mask, *it)]){
                        winFlag = true; break;
                    }
                }
                currDP[mask] = winFlag;
            } else {
                bool winFlag = true;
                for(auto it = moves.begin(); it != moves.end(); ++it){
                    if(!prevDP[removeBitFromMask(mask, *it)]){
                        winFlag = false; break;
                    }
                }
                currDP[mask] = winFlag;
            }
        }

        // Convert map back to bitset for next iteration
        prevDP.reset();
        for(auto &[mask, val] : currDP){
            if(val) prevDP.set(mask);
        }
    }

    // Count winning configurations using iterator loop
    ll totalWins = 0;
    for(size_t i=0; i<prevDP.size(); ++i) if(prevDP[i]) totalWins++;

    int totalConfigs = modExp(2, n);
    ll ans = (totalConfigs + (totalWins % MOD)) % MOD;
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--) solveCase();

    return 0;
}


