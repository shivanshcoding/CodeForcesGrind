#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
int removebit(int n, int bit)
{
    int msk = (1 << 22);
    int filtermask = msk - (1 << bit);
    return ((n >> 1) & filtermask) | (n & ((1 << bit) - 1));
}
const ll MOD = 1e9+7;
class mint
{
public:
    ll val;
    static ll mod_exp(ll a, ll b)
    {
        ll res = 1;
        a = a % MOD;
        while (b > 0)
        {
            if (b % 2 == 1)
                res = (res * a) % MOD;
            b /= 2;
            a = (a * a) % MOD;
        }
        return res;
    }
    static ll gcdExtended(ll a, ll b, ll *x, ll *y)
    {
        if (a == 0)
        {
            *x = 0, *y = 1;
            return b;
        }
        ll x1, y1;
        ll gcd = gcdExtended(b % a, a, &x1, &y1);
        *x = y1 - (b / a) * x1;
        *y = x1;
        return gcd;
    }
    static ll modInverse(ll a)
    {
        ll x, y;
        ll g = gcdExtended(a, MOD, &x, &y);
        g++;
        ll res = (x % MOD);
        if (res < 0)
            res += MOD;
        return res;
    }
    mint() { val = 0; }
    mint(ll x)
    {
        val = x % MOD;
        if (val < 0)
            val += MOD;
    }
    mint &operator+=(const mint &other)
    {
        val += other.val;
        if (val >= MOD)
            val -= MOD;
        return (*this);
    }
    mint &operator-=(const mint &other)
    {
        val -= other.val;
        if (val < 0)
            val += MOD;
        return (*this);
    }
    mint &operator*=(const mint &other)
    {
        val = (val * other.val) % MOD;
        return (*this);
    }
    mint &operator/=(const mint &other)
    {
        val = (val * modInverse(other.val)) % MOD;
        return (*this);
    }
    mint &operator=(const mint &other)
    {
        val = other.val;
        return (*this);
    }
    mint operator+(const mint &other) const { return mint(*this) += other; }
    mint operator-(const mint &other) const { return mint(*this) -= other; }
    mint operator*(const mint &other) const { return mint(*this) *= other; }
    mint operator/(const mint &other) const { return mint(*this) /= other; }
    bool operator==(const mint &other) const { return val == other.val; }
 
    mint operator++()
    {
        ++val;
        if (val == MOD)
            val = 0;
        return (*this);
    }
    mint operator++(int)
    {
        val++;
        if (val == MOD)
            val = 0;
        return mint(val - 1);
    }
    mint operator--()
    {
        --val;
        if (val == -1)
            val = MOD - 1;
        return (*this);
    }
    mint operator--(int)
    {
        val--;
        if (val == -1)
            val = MOD - 1;
        return mint(val + 1);
    }
 
    // ^ has very low precedence, careful!!
 
    template <typename T>
    mint &operator^=(const T &other)
    {
        val = mod_exp(val, other);
        return (*this);
    }
    template <typename T>
    mint operator^(const T &other) const { return mint(*this) ^= other; }
 
    mint &operator^=(const mint &other)
    {
        val = mod_exp(val, other.val);
        return (*this);
    }
    mint operator^(const mint &other) const { return mint(*this) ^= other; }
 
    template <typename T>
    explicit operator T() { return (T)val; }
    template <typename T>
    friend mint operator+(T other, const mint &M) { return mint(other) + M; }
    template <typename T>
    friend mint operator-(T other, const mint &M) { return mint(other) - M; }
    template <typename T>
    friend mint operator*(T other, const mint &M) { return mint(other) * M; }
    template <typename T>
    friend mint operator/(T other, const mint &M) { return mint(other) / M; }
    template <typename T>
    friend mint operator^(T other, const mint &M) { return mint(other) ^ M; }
 
    friend std::ostream &operator<<(std::ostream &output, const mint &M) { return output << M.val; }
    friend std::istream &operator>>(std::istream &input, mint &M)
    {
        input >> M.val;
        M.val %= MOD;
        return input;
    }
};
 
const int maxn = 20;
const int maxm = 30;
 
ll modpow(ll a , ll b ) {
    ll res = 1 ;
    a %= MOD;
    while( b > 0 ) {
        if( b&1 ) res = ( res*a ) % MOD;
        a = ( a*a ) % MOD;
        b >>= 1 ;
    }
    return res ;
}
 
int main()
{   int t;
    cin >> t;
    while(t--){
        bool pl = 1;
        int n, m;
        cin >> n >> m;
        int k,x;
        cin >> k;
        vector<int> good;
        for(int i=0;i<k;i++){
            cin >> x;
            good.push_back(x);
        }
        if(m==1){
            cout << 1<< "\n";
            continue;
        }
        vector<vector<vector<bool>>> dp(2, vector<vector<bool>>(n + 1));
        int cntt = 0;
        for (int i = 1; i <= n; i++)
        {
    
            dp[0][i].resize(1 << i);
            dp[1][i].resize(1 << i);
            if (i == 1)
            {
                for (int j = 0; j <= 1; j++)
                {
                    for (int k = 0; k <= 1; k++)
                    {
                        dp[j][i][k] = k;
                    }
                }
            }
            else
            {
                for (int msk = 0; msk < (1 << i); msk++)
                {
                    bool ans0 = 1;
                    bool ans1 = 0;
                    for (auto x :good)
                    {
                        if (x <= i)
                        {
                            cntt++;
                            int finmsk = removebit(msk, x - 1);
                            ans0 &= dp[1][i - 1][finmsk];
                            ans1 |= dp[0][i - 1][finmsk];
                        }
                        else
                        {
                            break;
                        }
                    }
                    dp[0][i][msk] = ans0;
                    dp[1][i][msk] = ans1;
                }
            }
        }
        mint finans = 0;
        for (int r = 0; r < (1<<n); r++)
        {   
            finans += 1+dp[pl][n][r];
            
        }
        cout << finans << endl;
    }
}