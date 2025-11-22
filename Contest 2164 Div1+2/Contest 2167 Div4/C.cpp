#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t; 
    cin >> t;
    while (t--) {
        
        int n;
        cin >> n;
        bool odd = false, even = false;
        vector<int> a(n);
        for (int i = 0, x; i < n; ++i) {
            cin >> a[i];
            if (a[i] % 2 == 0) even = true;
            else odd = true;
        }
        if (odd and even) sort(a.begin(), a.begin() + n);
        for (int i = 0; i < n; ++i) cout << a[i] << " \n"[i == n - 1]; 
    }
}