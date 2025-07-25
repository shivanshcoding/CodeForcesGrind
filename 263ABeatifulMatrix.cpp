#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b;
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            int ch;
            cin >> ch;
            if (ch == 1)
            {
                a = i;
                b = j;
            }
        }
    }
    cout << abs(3 - a) + abs(3 - b);
    return 0;
}
