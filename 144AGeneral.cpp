#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> soldiers(n);
    for (int i = 0; i < n; i++) {
        cin >> soldiers[i];
    }

    int max_height = *max_element(soldiers.begin(), soldiers.end());
    int min_height = *min_element(soldiers.begin(), soldiers.end());

    int max_index = find(soldiers.begin(), soldiers.end(), max_height) - soldiers.begin();
    int min_index = find(soldiers.rbegin(), soldiers.rend(), min_height) - soldiers.rbegin();
    min_index = (n - 1) - min_index;  // Convert to normal index

    int moves = max_index + (n - 1 - min_index);
    if (max_index > min_index) moves--;  // If tallest comes before shortest, one move overlaps.

    cout << moves << endl;
    return 0;
}
