#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    
    while (t--) {
        string k;
        cin >> k;

        bool found = false;
        for (int i = 0; i < (int)k.size() - 1; i++) {
            if (k[i] == k[i + 1]) {
                found = true;
                break; // Stop checking once we find a pair
            }
        }
        
        cout << (found ? 1 : k.size()) << '\n';
    }
    
    return 0;
}
