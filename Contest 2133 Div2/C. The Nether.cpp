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
    cin >> n;
    vector<int> L(n+1, 0);
    int st = 1;
    for (int i=1; i<=n; i++) {
        cout << "? " << i << " " << n;
        for (int j=1; j<=n; j++) {
            cout << " " << j;
        }
        cout << endl;
        cin >> L[i];
        if(L[i] > L[st]){
            st = i;
        }
    }
    
    unordered_map<int, vector<int>> mpp;
    for (int i=1; i<=n; i++) {
        mpp[L[i]].push_back(i);
    }
    
    vector<int> ans;
    ans.push_back(st);
    int curr = st;
    while (L[curr] > 1) {
        int next = L[curr] - 1;
        vector<int> c = mpp[next];
        if (c.size() == 1) {
            ans.push_back(c[0]);
            curr = c[0];
        } else {
            sort(all(c));
            int l = 0, h = c.size() - 1;
            while (l < h) {
                int mid = l+ ((h-l) / 2);
                cout << "? " << curr << " " << (mid - l + 2) << " " << curr;
                for (int i=l; i<=mid; i++) {
                    cout << " " << c[i];
                }
                cout << endl;
                int a;
                cin >> a;
                if (a == 2) {
                    h = mid;
                } else {
                    l = mid + 1;
                }
            }
            ans.push_back(c[l]);
            curr = c[l];
        }
    }
    
    cout << "! " << ans.size();
    for (int node : ans) {
        cout << " " << node;
    }
    cout << endl;
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}