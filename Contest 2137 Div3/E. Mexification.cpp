#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> apply_mex_operation(const vector<int>& data, int length) {
    // Frequency map using unordered_map instead of vector
    unordered_map<int,int> count_map;
    for (const int& val : data) {
        if (val >= 0 && val <= length) {
            count_map[val]++;
        }
    }

    // Find MEX using a simple loop since we have unordered_map
    int mex_value = 0;
    while (count_map.find(mex_value) != count_map.end() && count_map[mex_value] > 0) {
        ++mex_value;
    }

    vector<int> transformed(length);
    for (int idx = 0; idx < length; ++idx) {
        int current = data[idx];
        // If current is less than mex_value and unique in original, keep it; else replace with mex
        if (current < mex_value && count_map[current] == 1) {
            transformed[idx] = current;
        } else {
            transformed[idx] = mex_value;
        }
    }

    return transformed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;
    while (test_cases--) {
        int size; ll steps;
        cin >> size >> steps;

        vector<int> arr(size);
        for (int& elem : arr) cin >> elem;

        if (steps == 0) {
            ll total = accumulate(arr.begin(), arr.end(), 0LL);
            cout << total << '\n';
            continue;
        }

        vector<int> first_transform = apply_mex_operation(arr, size);
        ll first_sum = accumulate(first_transform.begin(), first_transform.end(), 0LL);

        if (steps % 2 == 1) {
            cout << first_sum << '\n';
            continue;
        }

        vector<int> second_transform = apply_mex_operation(first_transform, size);
        ll second_sum = accumulate(second_transform.begin(), second_transform.end(), 0LL);
        cout << second_sum << '\n';
    }

    return 0;
}
