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
ll t=1,n,m,k,a,b,q,x,y, MOD = 1e9+7;

void solve() {
    cin>>m>>n;
    if(m%2==0){
        cout<<(m/2)*n;
    }else if(n%2==0){
        cout<<(n/2)*m;
    }else{
        cout<< ((m-1)/2)*n + (n/2);
    }
}

int main() {
    fastio();
    // cin >> t;
    while (t--) solve();
    return 0;
}