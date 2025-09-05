#include <bits/stdc++.h>
using namespace std;

void test() {
    int n, k;
    cin >> n >> k;
    int m = k - 1;

    vector<int> l(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    vector<int> a(n), b(n);
    long long y = 0;
    for (int i = 0; i < n; i++) {
        a[i] = max(l[i], r[i]);
        b[i] = min(l[i], r[i]);
        y += a[i];
    }

    sort(b.begin(), b.end(), greater<>());
    for (int i = 0; i < m; i++) {
        y += b[i];
    }

    long long x = y + 1;
    cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        test();
    }
    
    return 0;
}