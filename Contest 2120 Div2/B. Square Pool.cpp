#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    int n, s, ans = 0, dxi, dyi, xi, yi;
    while(t--) {
        cin >> n >> s;
        
        for (int i = 0; i < n; i++) {
            cin >> dxi >> dyi >> xi >> yi;
            if (dxi == dyi) ans += (xi == yi);
            else ans += (xi + yi == s);
        }
        
        cout << ans << '\n';
        ans = 0;
    }
    return 0;
}