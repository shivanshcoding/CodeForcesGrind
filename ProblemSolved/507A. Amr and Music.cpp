#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        pq.push({x, i});
    }
    int ans = 0;
    vector<int> ansArr;
    while (!pq.empty() && pq.top().first <= k)
    {
        auto [x, i] = pq.top();
        pq.pop();
        ans++;
        ansArr.push_back(i);
        k -= x;
    }
    cout << ans << endl;
    for (int i : ansArr)
    {
        cout << i << " ";
    }
    return 0;
}