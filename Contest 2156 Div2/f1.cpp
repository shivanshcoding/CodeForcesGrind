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

class ArrayTransformer {
    int n;
    vector<int> values;
    unordered_map<int, int> indexMap;

    bool stepReorder() {
        bool modified = false;
        for (int x = 1; x + 2 <= n; ++x) {
            int i1 = indexMap[x];
            int i2 = indexMap[x + 1];
            int i3 = indexMap[x + 2];

            // Condition to trigger the rearrangement
            if (i3 < i1 && i3 < i2) {
                values[i3] -= 2;
                values[i1] += 1;
                values[i2] += 1;

                // Update index mapping
                indexMap[x] = i3;
                indexMap[x + 1] = i1;
                indexMap[x + 2] = i2;

                modified = true;
            }
        }
        return modified;
    }

public:
    explicit ArrayTransformer(int size) : n(size), values(size + 1, 0) {}

    void readData() {
        for (int i = 1; i <= n; ++i) {
            cin >> values[i];
            indexMap[values[i]] = i;
        }
    }

    void transform() {
        if (n < 3) return;
        for (;;) {
            if (!stepReorder()) break;
        }
    }

    void printArray() const {
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << values[i];
        }
        cout << '\n';
    }
};

class Runner {
public:
    void execute() {
        fastio();

        int testCount;
        cin >> testCount;

        while (testCount--) {
            int len;
            cin >> len;

            ArrayTransformer transformer(len);
            transformer.readData();
            transformer.transform();
            transformer.printArray();
        }
    }
};

int main() {
    Runner().execute();
    return 0;
}
