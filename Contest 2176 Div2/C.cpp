#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve()
{
    int n;
    cin >> n;
    vector<ll> odds, evens;
    for (int i = 0; i < n; ++i)
    {
        ll val;
        cin >> val;
        if (val % 2 != 0)
            odds.push_back(val);
        else
            evens.push_back(val);
    }

    sort(odds.rbegin(), odds.rend());
    sort(evens.rbegin(), evens.rend());

    int num_odds = odds.size();
    int num_evens = evens.size();

    vector<ll> pref_evens(num_evens + 1, 0);
    for (int i = 0; i < num_evens; ++i)
    {
        pref_evens[i + 1] = pref_evens[i] + evens[i];
    }

    ll max_odd_val = (num_odds > 0) ? odds[0] : -1;

    for (int k = 1; k <= n; ++k)
    {
        int min_x = max(1, k - num_evens);

        if (min_x % 2 == 0)
            min_x++;

        // Check if a valid configuration exists
        if (min_x > num_odds || min_x > k)
        {
            cout << 0 << (k == n ? "" : " ");
            continue;
        }

        // Calculate y corresponding to the minimal valid x
        int y = k - min_x;

        // Score = Largest Available Odd + Sum of Largest y Evens
        ll ans = max_odd_val + pref_evens[y];
        cout << ans << (k == n ? "" : " ");
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}