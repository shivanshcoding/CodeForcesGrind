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

void solve() {
    cin>>n;
    if((n%4)==2){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n/2;i++){
        cout<<i*2<<" ";
    }
    int bit = 0;
    for(int i=1;i<=n/2;i++){
        cout<<i*2-1 + 2*bit<<" ";
        if(i==n/4) bit =1;
    }
    cout<<endl;
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}