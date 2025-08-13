#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        long long c;
        cin >> n >> c;

        vector<long long> a(n);
        for (auto &x : a) cin >> x;

        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());

        int coins = 0;
        int time = 0;
        for (int i = 0; i < n; ++i)
        {
            if (a[i] > c)
            {
                coins++;
            }
            else
            {
                int count = floor(log2(c / a[i])) + 1;
                if (time < count)
                {
                    time++;
                }
                else
                {
                    coins++;
                }
            }
        }
        cout << coins << '\n';
    }

    return 0;
}
