#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int min_len = INT_MAX;
    int best_a = -1, best_b = -1;

    for (int b = 0; b * 7 <= n; ++b) {
        int rem = n - b * 7;
        if (rem % 4 == 0) {
            int a = rem / 4;
            if (a + b < min_len || (a + b == min_len && b < best_b)) {
                min_len = a + b;
                best_a = a;
                best_b = b;
            }
        }
    }

    if (best_a == -1) {
        cout << -1;
    } else {
        cout << string(best_a, '4') << string(best_b, '7');
    }

    return 0;
}
