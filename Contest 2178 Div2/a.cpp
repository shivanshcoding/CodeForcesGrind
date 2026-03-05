#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    string s;
    cin >> s;
    int y = count(s.begin(), s.end(), 'Y');
    if (y > 1) cout << "NO" << endl;
    else cout << "YES" << endl;
}
 
int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}