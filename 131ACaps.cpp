#include <bits/stdc++.h>
using namespace std;

int main() {
    string k;
    cin >> k;
    int n = k.size();

    // Check if all characters are uppercase OR all except first are uppercase
    bool allUpper = true;
    bool exceptFirstUpper = true;

    for (int i = 0; i < n; i++) {
        if (islower(k[i])) allUpper = false; // If any letter is lowercase, allUpper becomes false
        if (i > 0 && islower(k[i])) exceptFirstUpper = false; // If a letter except first is lowercase
    }

    if (allUpper || exceptFirstUpper) {
        // Convert case
        for (int i = 0; i < n; i++) {
            if (islower(k[i])) 
                k[i] = toupper(k[i]);
            else 
                k[i] = tolower(k[i]);
        }
    }

    cout << k;
    return 0;
}
