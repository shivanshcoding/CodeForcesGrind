#include <bits/stdc++.h>
using namespace std;

int main() {
    string k;
    cin >> k;
    
    int n = k.size();
    
    for (int i = 0; i < n; i++) {
        int digit = k[i] - '0';
        int complement = 9 - digit;

        // Ensure the first digit does not become zero
        if (i == 0 && complement == 0) continue;

        if (complement < digit) {
            k[i] = complement + '0';
        }
    }

    cout << k << endl;
    return 0;
}
