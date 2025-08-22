#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int len = s.size();
    if(len==1){
        cout<<0;
        return 0;
    }
    int ans = len / 2;
    if (len % 2 == 1) {
        // check if s is a power of 4
        bool power4 = (s[0] == '1');
        for (int i = 1; i < len; i++) {
            if (s[i] != '0') { power4 = false; break; }
        }
        if (!power4) ans++;
    }
    
    cout << ans << "\n";
    return 0;
}
