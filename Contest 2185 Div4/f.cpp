#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        int num_cows = (1<<n);
        vector<int> cows(num_cows); for (auto &x: cows) cin >> x;

        vector<int> prefix(num_cows); prefix[0] = cows[0];
        for (int i = 1; i < num_cows; i++) {
            prefix[i] = cows[i] ^ prefix[i-1];
        }

        while (q--) {
            int cow_idx, skill_level;
            cin >> cow_idx >> skill_level;
            cow_idx--;

            int curr_position = 0;
            for (int i = 0; i < n; i++) {
                int size = (1<<i);
                int leader_idx = cow_idx / size;

                int leader_value = prefix[(size)*(leader_idx+1)-1] ^ (leader_idx == 0 ? 0 : prefix[(size)*(leader_idx)-1]);
                leader_value ^= cows[cow_idx];
                leader_value ^= skill_level;
                
                int enemy_value;
                if (leader_idx % 2 == 0) {
                    enemy_value = prefix[(size)*(leader_idx+2)-1] ^ prefix[(size)*(leader_idx+1)-1];
                }
                else {
                    enemy_value = prefix[(size)*(leader_idx)-1] ^ ((leader_idx-1) == 0 ? 0 : prefix[(size)*(leader_idx-1)-1]);
                }
                if (leader_value < enemy_value || (leader_value == enemy_value && leader_idx % 2 == 1)) {
                    curr_position += size;
                }
            }

            cout << curr_position << "\n";
        }
    } 
}