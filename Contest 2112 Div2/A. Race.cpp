#include <bits/stdc++.h>
 
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, x, y;
    cin >> a >> x >> y;
    cout << ((a < x) == (a < y) ? "YES" : "NO") << '\n';
  }
}