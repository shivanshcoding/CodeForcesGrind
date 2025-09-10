#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
 
void solve(){
    int n,t;
    cin >> n >> t;
    ll ans = 0;
    vector <int> a(n);
    for(int i = 0;i < n;i ++) cin >> a[i];
    sort(a.begin(),a.begin() + n,greater <int>());
    for(int i = 0;i < n;i ++) ans += 1ll * a[i] * max(0,t - i);
    cout << ans << '\n';
}
 
int main(){
    ios::sync_with_stdio(false);
    int TC;
    cin >> TC;
    while(TC --){
        solve();
    }
    return 0;
}