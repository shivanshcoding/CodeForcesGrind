#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> cnt(k + 1, 0);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    int pairs = 0, odd_count = 0;
    for (int c : cnt) {
        pairs += c / 2;
        if (c % 2) odd_count++;
    }

    int sets_needed = (n + 1) / 2;
    int use_pairs = min(pairs, sets_needed);

    int answer = 2 * use_pairs + min(sets_needed - use_pairs, odd_count);

    cout << answer << "\n";
    return 0;
}
