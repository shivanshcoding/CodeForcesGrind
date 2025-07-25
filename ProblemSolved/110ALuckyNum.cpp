#include <bits/stdc++.h>
using namespace std;

int main() {
    string n;
    cin >> n;

    int lucky_count = 0;
    for (char c : n) {
        if (c == '4' || c == '7') {
            lucky_count++;
        }
    }

    cout << ((lucky_count == 4 || lucky_count == 7) ? "YES" : "NO") << endl;
    
    return 0;
}
