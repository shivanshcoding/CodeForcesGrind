#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cards(n, vector<int>(m));
    vector<int> cow_for_card(n * m);
    vector<int> min_card(n, n * m);
    vector<int> p(n);

    // Reading input and determining which cow has which card
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> cards[i][j];
            cow_for_card[cards[i][j]] = i;
            min_card[i] = min(min_card[i], cards[i][j]);
        }
    }

    // Assign cows to permutation positions based on their minimum card
    for (int i = 0; i < n; ++i) {
        if (min_card[i] >= n) {
            cout << -1 << '\n';
            return;
        }
        p[min_card[i]] = i;
    }

    // Validate each cow's cards
    for (int i = 0; i < n; ++i) {
        sort(cards[i].begin(), cards[i].end());
        for (int j = 1; j < m; ++j) {
            if (cards[i][j] - cards[i][j - 1] != n) {
                cout << -1 << '\n';
                return;
            }
        }
    }

    // Output the permutation (1-based indexing)
    for (int i = 0; i < n; ++i) {
        cout << p[i] + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}


