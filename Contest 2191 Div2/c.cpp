#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int t;
    cin >> t;
    for (int z = 0; z < t; z++)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        if (is_sorted(s.begin(), s.end()))
        {
            cout << "Bob" << endl;
        }
        else
        {
            int count1 = 0;
            int count0 = 0;
            cout << "Alice" << endl;
            for (char c : s)
            {
                if (c == '1')
                {
                    count1++;
                }
                else
                {
                    count0++;
                }
            }
            int start = n;
            int end = -1;
            int count = 0;
            vector<int> indexes;
            for (int i = 0; i < n; i++)
            {
                if (count0 != 0)
                {
                    if (s[i] == '0')
                    {
                        count0--;
                    }
                    else
                    {
                        count0--;
                        indexes.push_back(i);
                        count++;
                    }
                }
                else
                {
                    if (s[i] == '0')
                    {
                        indexes.push_back(i);
                        count++;
                    }
                }
            }
            cout << count << endl;
            for (int i : indexes)
            {
                cout << i + 1 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}