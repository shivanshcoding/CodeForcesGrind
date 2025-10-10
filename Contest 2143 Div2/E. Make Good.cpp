#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define debug(x) #x << " = " << x << '\n'

using ll = long long;
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"

void solve()
{
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    if (s == "))))))))")
    {
        std::cout << "(()(()))";
        return;
    }
    if (n % 2 == 1)
    {
        std::cout << -1;
        return;
    }

    int delta = 0;

    assert((int)s.size() == n);

    for (int i = 0; i < (int)s.size(); i++)
    {
        int value = (s[i] == '(' ? +1 : -1);
        if (i & 1)
        {
            value *= -1;
        }
        delta += value;
    }

    if (delta == -n || std::abs(delta) % 4 != n % 4)
    {
        std::cout << -1;
        return;
    }

    int plus = (n + delta) / 2;
    int minus = (n - delta) / 2;

    assert(minus % 2 == 0);

    std::cout << "(";
    for (int i = 0; i < minus / 2; i++)
    {
        std::cout << "()";
    }
    std::cout << ")";
    for (int i = 0; i < (plus - 2) / 2; i++)
    {
        std::cout << "()";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    std::cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        solve();
        std::cout << '\n';
    }

    return 0;
}