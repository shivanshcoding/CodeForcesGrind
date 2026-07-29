#include <bits/stdc++.h>
using namespace std;
using usl = unsigned long long;
#define nl                "\n"
#define int               long long
#define F(i, j, n)        for(int i = j; i <= n; i++)
#define R(i, j, n)        for(int i = j; i >= n; i--)
#define vin(a)            for(auto &x : a) cin>> x
#define vout(a)           for(auto &x : a) cout<< x<<" "
#define all(a)            a.begin(),a.end()
#define rall(a)           a.rbegin(),a.rend()
#define yes               cout<<"YES\n"
#define no                cout<<"NO\n"

void f() {
    int n, s = 0;
    cin>>n;
    vector<int> a(n);
    vin(a);

    F(i, 1, n - 2) {
        if (a[i] == -1) a[i] = 0;
    }

    if (a[0] == -1 && a[n - 1] == -1){
        a[0] = 0;
        a[n - 1] = 0;
    }else if (a[0] == -1){
        a[0] = a[n - 1];
    }else if (a[n - 1] == -1){
        a[n - 1] = a[0];
    }

    cout<<abs(a[0] - a[n - 1])<<nl;
    vout(a);
    cout<<nl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t = 1;
  cin >> t;
  while(t--) f();
}