#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
int er(int x)
{
    int cnt = 0;
    while (x > 0)
    {
        cnt++;
        x = x >> 1;
    }
    return cnt;
}
void solve()
{
    int n;
    cin >> n;
    int sum = 0;
    vector<int> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum = sum ^ a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        sum = sum ^ b[i];
    }
    if (sum == 0)
        cout << "Tie" << endl;
    else
    {
        int cnt = er(sum);
        for (int i = n; i >= 1; i--)
        {
            int num = a[i] ^ b[i];
            int p=pow(2,cnt-1);
            num=num&p;
            if (num==pow(2,cnt-1))
            {
                if (i % 2 != 0)
                {
                    cout << "Ajisai" << endl;
                    return;
                }
                else
                {
                    cout << "Mai" << endl;
                    return;
                }
            }
        }
        cout << 1 << endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    // solve();
    return 0;
}