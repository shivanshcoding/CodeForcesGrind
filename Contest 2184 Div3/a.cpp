#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        if (n == 2) cout << "2\n";
        if (n == 3) cout << "3\n";
        if (n >= 4) cout << n % 2 << '\n';
    }
    
    return 0;
}