#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(x) (x).begin(), (x).end()
#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define eb emplace_back 
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pdd = pair<double, double>;
using pll = pair<long long, long long>;
using i128 = __int128;
 
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int inf = 0x3f3f3f3f;
const ll INF = 4e18;
const int N = 0;
 
void solve()
{
    int n;
    cin >> n;
 
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
 
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += (a[i] % 2 != i % 2);
    cout << (cnt == 0 || cnt == n ? "YES" : "NO") << endl;
}
 
int main()
{
    fastio();
 
    int T = 1;
    cin >> T;
 
    while (T--)
        solve();
 
    return 0;
}