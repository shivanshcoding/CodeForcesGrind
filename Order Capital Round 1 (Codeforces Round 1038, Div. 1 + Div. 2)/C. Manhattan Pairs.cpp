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
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,k,a,b,q,x,y, MOD = 1e9+7;

struct Point {
    ll x, y, id;
};

void solve() {
    cin >> n;
    vector<Point> pts(n);
    for (ll i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    vector<ll> Xl(n), Yl(n);
    
    // Split by x
    vector<Point> sortedX = pts;
    sort(sortedX.begin(), sortedX.end(), [](auto &a, auto &b) {
        return a.x < b.x;
    });
    for (ll i = 0; i < n/2; i++) Xl[sortedX[i].id-1] = 1;

    // Split by y
    vector<Point> sortedY = pts;
    sort(sortedY.begin(), sortedY.end(), [](auto &a, auto &b) {
        return a.y < b.y;
    });
    for (ll i = 0; i < n/2; i++) Yl[sortedY[i].id-1] = 1;

    // Partition into A,B,C,D
    vector<ll> A, B, C, D;
    for (ll i = 0; i < n; i++) {
        bool inXl = Xl[i], inYl = Yl[i];
        if (inXl && inYl) A.push_back(i+1);
        else if (!inXl && !inYl) B.push_back(i+1);
        else if (inXl && !inYl) C.push_back(i+1);
        else D.push_back(i+1);
    }

    // Pair A-B
    for (ll i = 0; i < (int)A.size(); i++) {
        cout << A[i] << " " << B[i] << "\n";
    }
    // Pair C-D
    for (ll i = 0; i < (int)C.size(); i++) {
        cout << C[i] << " " << D[i] << "\n";
    }
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}