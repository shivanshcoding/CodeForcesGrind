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

class ShapeAnalyzer {
    long long answer = 0;

    struct SingleTracker {
        long long hi = 0, nxt = 0;
        void feed(long long val) {
            if (val > hi) {
                nxt = hi;
                hi = val;
            } else if (val > nxt) {
                nxt = val;
            }
        }
    };

    inline void update_best(long long sum, long long edge) {
        if (2 * edge < sum) answer = max(answer, sum);
    }

public:
    void process_case() {
        int n;
        cin >> n;

        vector<long long> vals(n);
        for (auto &x : vals) cin >> x;

        unordered_map<long long, int> freq;
        freq.reserve(n * 2);
        for (auto &x : vals) ++freq[x];

        vector<pair<long long, int>> arr(freq.begin(), freq.end());
        sort(arr.begin(), arr.end());

        SingleTracker track;
        long long total_pairs = 0;

        for (auto &[num, count] : arr) {
            long long local_sum = total_pairs;
            if (count >= 1) {
                if (local_sum) update_best(local_sum + num, num);
                if (track.hi) update_best(local_sum + track.hi + num, num);
            }

            if (count >= 2) {
                long long pair_used = (count / 2) * 2LL * num;
                long long temp_sum = local_sum + pair_used;

                long long t1 = track.hi, t2 = track.nxt;
                if (count & 1) {
                    if (num > t1) {
                        t2 = t1;
                        t1 = num;
                    } else if (num > t2) {
                        t2 = num;
                    }
                }

                update_best(temp_sum, num);
                if (t1) update_best(temp_sum + t1, num);
                if (t2) update_best(temp_sum + t1 + t2, num);
            }

            total_pairs += (count / 2) * 2LL * num;
            if (count & 1) track.feed(num);
        }

        cout << answer << '\n';
        answer = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    ShapeAnalyzer solver;
    while (t--) solver.process_case();

    return 0;
}
