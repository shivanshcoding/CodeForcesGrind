#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    string k;
    cin >> n >> k;
    
    unordered_map<char, int> freq;
    
    for (char c : k) {
        freq[c]++;
    }
    
    string unit = ""; // The base pattern that will be repeated n times
    
    for (auto it : freq) {
        if (it.second % n != 0) { // If frequency is not a multiple of n, return -1
            cout << -1;
            return 0;
        }
        unit += string(it.second / n, it.first); // Append character multiple times
    }
    
    string result = "";
    for (int i = 0; i < n; i++) {
        result += unit; // Repeat the base unit n times
    }
    
    cout << result;
    return 0;
}
