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

// Function to solve a single test case
string solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int alice_eats = 0;
    int bob_eats = 0;

    int left = 0;
    int right = n - 1;

    bool is_alice_turn = true;

    while (left <= right) {
        if (is_alice_turn) {
            // Alice's turn: find the leftmost 'A'
            bool found_a = false;
            while (left <= right) {
                if (s[left] == 'A') {
                    alice_eats++;
                    left++;
                    found_a = true;
                    break;
                }
                left++;
            }
            // If no 'A' is left for Alice, her turns are over
            if (!found_a) {
                break;
            }
        } else {
            // Bob's turn: find the rightmost 'B'
            bool found_b = false;
            while (left <= right) {
                if (s[right] == 'B') {
                    bob_eats++;
                    right--;
                    found_b = true;
                    break;
                }
                right--;
            }
            // If no 'B' is left for Bob, his turns are over
            if (!found_b) {
                break;
            }
        }
        is_alice_turn = !is_alice_turn;
    }

    if (alice_eats > bob_eats) {
        return "Alice";
    } else {
        return "Bob";
    }
}

int main() {
    fastio();
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": " << solve() << "\n";
    }
    return 0;
}