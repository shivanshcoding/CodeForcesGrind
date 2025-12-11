#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#define prDouble(x) cout << fixed << setprecision(10) << x
#define fastio()                 \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};                               // for grid
vector<ll> ddx = {1, 1, 0, -1, -1, -1, 0, 1}, ddy = {0, 1, 1, 1, 0, -1, -1, -1}; // 8 directions
template <typename T>
void read(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}
template <typename T>
void printv(const vector<T> &v)
{
    for (auto &x : v)
        cout << x << ' ';
}
template <typename T>
void print2d(const vector<vector<T>> &v)
{
    for (auto &row : v)
    {
        for (auto &x : row)
            cout << x << ' ';
        cout << '\n';
    }
}
ll t = 1, n, m, p, q, r, k, a, b, c, x, y, z;
const ll INF = 1e18, MOD = 1e9 + 7;

class BinaryCase
{
public:
    int length;
    string bits;

    BinaryCase() : length(0), bits() {}
    void readFromStream()
    {
        cin >> length;
        cin >> bits;
    }
};

class GapAnalyzer
{
public:
    explicit GapAnalyzer(const BinaryCase &bc) : n(bc.length), s(bc.bits)
    {
        collectOnePositions();
    }

    int maxZeroGapCircular()
    {
        if (onePos.empty())
            return 0;
        if ((size_t)n == onePos.size())
            return 0;

        int best = 0;
        for (size_t i = 0; i < onePos.size(); ++i)
        {
            int cur = onePos[i];
            int nxt = onePos[(i + 1) % onePos.size()];
            int gap = (nxt > cur) ? (nxt - cur - 1) : (nxt + n - cur - 1);
            best = max(best, gap);
        }
        return best;
    }

private:
    int n;
    string s;
    vector<int> onePos;

    void collectOnePositions()
    {
        onePos.clear();
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '1')
                onePos.push_back(i);
        }
    }
};

int main()
{
    cin >> t;
    while (t--)
    {
        BinaryCase bc;
        bc.readFromStream();
        GapAnalyzer analyzer(bc);
        int res = analyzer.maxZeroGapCircular();
        cout << res << '\n';
    }

    return 0;
}
