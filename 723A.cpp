#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    // Sort the positions
    vector<int> v = {a, b, c};
    sort(v.begin(), v.end());
    // The best meeting point is the middle one (median)
    cout << (v[2] - v[0]) << endl;
    return 0;
}
