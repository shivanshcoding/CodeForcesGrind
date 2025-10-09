#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

void solve()
{
    int n;
    cin >> n;
    vector<int> ord(n * n + 1);
    iota(all(ord), 0);
    auto query = [&](vector<int> v)
    {
        cout << "? " << sz(v);
        for (auto &x : v)
            cout << " " << x + 1;
        cout << endl;
        int y;
        cin >> y;
        v.resize(y);
        for (auto &x : v)
            cin >> x, x--;
        return v;
    };
    vector<int> dp(n * n + 1, n);
    for (int i = 0; i < n; i++)
    {
        auto cur_ord = query(ord);
        if (sz(cur_ord) > n)
        {
            cout << "!";
            for (int i = 0; i < n + 1; i++)
                cout << " " << cur_ord[i] + 1;
            cout << endl;
            return;
        }
        vector<int> new_ord;
        for (auto &x : ord)
        {
            if (!binary_search(all(cur_ord), x))
            {
                new_ord.push_back(x);
            }
            else
                dp[x] = i;
        }
        ord = new_ord;
    }
    int cur = n;
    vector<int> ans;
    for (int i = n * n; i >= 0; i--)
    {
        if (dp[i] == cur)
        {
            ans.push_back(i);
            cur--;
        }
    }
    if (sz(ans) != n + 1)
    {
        cerr << cur << endl;
        for (auto &x : dp)
            cerr << x << " ";
        cerr << endl;
    }
    reverse(all(ans));
    assert(sz(ans) == n + 1);
    cout << "!";
    for (auto &x : ans)
        cout << " " << x + 1;
    cout << endl;
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
        solve();
}