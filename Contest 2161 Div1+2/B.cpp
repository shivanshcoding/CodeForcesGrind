#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<pair<int, int>> indexs;
        set<int> pos1, pos2;
        int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                char c;
                cin >> c;
                if (c == '#')
                {
                    indexs.push_back({i, j});
                    pos1.insert(i + j);
                    pos2.insert(i - j);
                    minx = min(minx, i);
                    maxx = max(maxx, i);
                    miny = min(miny, j);
                    maxy = max(maxy, j);
                }
            }
        }

        if (indexs.size() == 0 or indexs.size() == 1)
            cout << "YES" << endl;
        else if ((*--(pos1.end()) - *pos1.begin() <= 1) or (*--(pos2.end()) - *pos2.begin() <= 1))
        {
            // if((pos1.size() <= 2)  or (pos2.size() <= 2) ){
            cout << "YES" << endl;
        }
        else if (indexs.size() == 4)
        {
            if (maxy - miny == 1 and maxx - minx == 1)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else
            cout << "NO" << endl;
    }
}