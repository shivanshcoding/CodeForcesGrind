#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> vec(n); 
        for (auto &x: vec) cin >> x;

        cout << *max_element(vec.begin(), vec.end()) * n << "\n";
    }
}