#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string k;
        cin >> k;

        int first = k.find('1');
        int last = k.rfind('1');

        if (first == string::npos) {
            cout << 0 << endl;
            continue;
        }

        int ans = 0;
        for (int i = first; i < last; i++) {
            if (k[i] == '0') ans++;
        }
        
        cout << ans << endl;
    }
    return 0;
}
