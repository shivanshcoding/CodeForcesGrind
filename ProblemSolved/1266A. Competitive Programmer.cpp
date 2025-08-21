#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int sum = 0, zero = 0, even = 0;
        for (char c : s) {
            int d = c - '0';
            sum += d;
            if (d == 0) zero++;
            if (d % 2 == 0) even++;
        }
        if (zero > 0 && sum % 3 == 0 && (zero > 1 || even > 1)) {
            cout << "red\n";
        } else {
            cout << "cyan\n";
        }
    }
    return 0;
}
