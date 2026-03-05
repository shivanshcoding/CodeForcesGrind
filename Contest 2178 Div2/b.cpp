#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    string s; cin >> s;
    s = "u" + s + "u";
    int ans = 0;
    for(int i = 1; i < (int) s.length(); i++) {
        if(s[i - 1] == 'u' && s[i] == 'u') {
            s[i] = 's';
            ans++;
        }
    }
    cout << ans << endl;
}
 
int main() {
    int T; cin >> T;
    while(T--) {
        solve();
    }
}