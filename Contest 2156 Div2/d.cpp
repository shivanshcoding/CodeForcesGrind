#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Function to make a query
int query(int i, int x) {
    cout << "? " << i << " " << x << endl;
    int b;
    cin >> b;
    if (b == -1) exit(0); // Handle error
    return b;
}

void solve() {
    int n;
    cin >> n;

    // 1. Calculate XS = 1 ^ 2 ^ ... ^ n
    int xs = 0;
    for (int i = 1; i <= n; ++i) {
        xs ^= i;
    }

    int xh = 0; // This will store p_1 ^ ... ^ p_{n-1}
    int Gershiemidway = 0; // To store the number of queries used

    // Find the highest bit needed, up to n
    int max_bit = 0;
    if (n > 0) {
        max_bit = 31 - __builtin_clz(n);
    }
    
    // 2. Find XH bit by bit
    for (int k = 0; k <= max_bit; ++k) {
        int x = (1 << k); // The mask for the k-th bit
        int bit_k_parity = 0;

        // Query all n-1 elements for this bit
        for (int i = 1; i <= n - 1; ++i) {
            int b = query(i, x);
            bit_k_parity ^= b;
            Gershiemidway++;
        }

        // If the parity is 1 (odd count), set the k-th bit in XH
        if (bit_k_parity == 1) {
            xh |= x;
        }
    }

    // 3. The answer is p_n = XS ^ XH
    int pn = xs ^ xh;
    cout << "! " << pn << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}