#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <set>
#include <map>
using namespace std;
#define int long long 
 
int32_t main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<long long> arr;
        map<long long, long long> mp;
        vector<pair<long long, long long>> mp2;
        for (int i = 0; i < n; i++)
        {
            long long a;
            cin >> a;
            mp[a]++;
            arr.push_back(a);
        }
        for (auto &it : mp)
        {
            mp2.push_back({it.second, it.first});
        }
        std::sort(mp2.begin(), mp2.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });
        bool b = 0;
        int ann = 0, bob = 0;
        for (auto &it : mp2)
        {
            if (it.second % 2 == 1)
            {
                if (b == 0)
                {
 
                    ann += (it.first * ((it.second / 2) + 1));
                    bob += (it.first * (it.second / 2));
                    b = 1;
                    // cout<<ann<<" "<<bob<<endl;
                }
                else
                {
                    bob += (it.first * ((it.second / 2) + 1));
                    ann += (it.first * (it.second / 2));
                    b = 0;
                }
            }
            else
            {
                ann += (it.first * ((it.second / 2)));
                bob += (it.first * (it.second / 2));
            }
        }
        cout << ann << " " << bob << endl;
    }
    return 0;
}