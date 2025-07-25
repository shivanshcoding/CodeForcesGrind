#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int maxLen = 1, curLen = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            curLen++;
        } else {
            maxLen = max(maxLen, curLen);
            curLen = 1;
        }
    }
    maxLen = max(maxLen, curLen); // Final check after loop
    
    cout << maxLen << endl;
    return 0;
}
