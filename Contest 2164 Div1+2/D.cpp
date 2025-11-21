#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, kmax;
    cin >> n >> kmax;
    string s, t;
    cin >> s >> t;
    vector<vector<int>> pos(26);
    for (int i = 0; i < n; i++)
    {
        pos[s[i] - 'a'].push_back(i);
    }
    vector<int> f(n, n);
    int mn = n;
    for (int i = n - 1; i >= 0; i--)
    {
        int c = t[i] - 'a';
        while (!pos[c].empty() && mn < pos[c].back())
        {
            pos[c].pop_back();
        }
        if (!pos[c].empty())
        {
            int x = pos[c].back();
            f[i] = x;
            mn = min(mn, x);
            if (i == x)
            {
                pos[c].pop_back();
            }
        }
    }
    int K = -n;
    for (int i = 0; i < n; i++)
    {
        K = max(K, i - f[i]);
    }
    if (count(f.begin(), f.end(), n) || K > kmax)
    {
        cout << -1 << '\n';
        return;
    }
    cout << K << '\n';
    for (int step = 1; step <= K; step++)
    {
        string ns = s;
        for (int j = 0; j < n; j++)
        {
            if (j - f[j] >= step)
            {
                ns[j] = s[j - 1];
            }
        }
        s = ns;
        cout << s << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
