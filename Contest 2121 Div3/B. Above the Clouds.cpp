#include<bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> cnt(26, 0);
        for (auto c : s) cnt[c - 'a']++;
        int flag = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] >= 3) flag = 1;
            else if (cnt[i] == 2 && (s[0] - 'a' != i || s.back() - 'a' != i)) flag = 1;
        }
        if (flag) cout << "Yes" << '\n';
        else cout << "No" << '\n';
    }
    return 0;
}