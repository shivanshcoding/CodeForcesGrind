#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n;
    vector<int> a(n);
    for(auto &i : a) cin >> i;
    cin>>x;
    if(n == 1) {
        if(a[0] == x) {
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;
        }
        return;
    }
    for(int i = 0; i < n - 1; i++) {
        int mn = min(a[i], a[i + 1]);
        int mx = max(a[i], a[i + 1]);
        if(mn <= x && x <= mx) {
            cout<<"YES"<<endl;
            return;
        }    
    }
    cout<<"NO"<<endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}