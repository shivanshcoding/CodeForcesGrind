#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    if(k==n){
        string ans(n,'-');
        cout<<ans<<"\n";
        return;
    }

    int top_min = 1, top_max = 1;           // smallest and largest card removed from top
    int bottom_max = n, bottom_min = n;     // largest and smallest card removed from bottom

    for (char c : s) {
        if (c == '0') {
            top_min++;
            top_max++;
        } else if (c == '1') {
            bottom_max--;
            bottom_min--;
        } else { // '2'
            top_max++;
            bottom_min--;
        }
    }

    string ans;
    ans.reserve(n);

    for (int i = 1; i <= n; i++) {
        if (i < top_min || i > bottom_max) {
            ans.push_back('-');  // definitely removed
        } else if (i >= top_max && i <= bottom_min) {
            ans.push_back('+');  // definitely present
        } else {
            ans.push_back('?');  // uncertain
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
