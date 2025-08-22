#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; 
    if (!(cin >> n)) return 0;
    long long sx = 0, sy = 0, sz = 0;
    for (int i = 0; i < n; ++i) {
        int x, y, z; 
        cin >> x >> y >> z;
        sx += x; sy += y; sz += z;
    }
    cout << ((sx == 0 && sy == 0 && sz == 0) ? "YES" : "NO") << "\n";
    return 0;
}
