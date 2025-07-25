#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> nums(2 * n);
        
        for (int i = 0; i < 2 * n; i++) {
            cin >> nums[i];
        }

        sort(nums.begin(), nums.end());

        cout << nums[n] - nums[n - 1] << endl;  // Correct indexing
    }
    return 0;
}
