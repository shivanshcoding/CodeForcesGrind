#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, ra, ca, rb, cb;
        cin >> n >> ra >> ca >> rb >> cb;
        int ans = 0;
        if (rb > ra)
            ans = max(ans, rb);
        else if (rb < ra)
            ans = max(ans, n - rb);
        if (cb > ca)
            ans = max(ans, cb);
        else if (cb < ca)
            ans = max(ans, n - cb);
        cout << ans << '\n';
    }
}