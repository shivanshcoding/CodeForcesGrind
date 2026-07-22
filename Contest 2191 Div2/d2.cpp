#include <bits/stdc++.h>
using namespace std;
struct custom_hash {
   static uint64_t splitmix64(uint64_t x) {
       x += 0x9e3779b97f4a7c15;
       x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
       x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
       return x ^ (x >> 31);
   }
size_t operator()(uint64_t x) const {
       static const uint64_t FIXED_RANDOM =
       chrono::steady_clock::now().time_since_epoch().count();
       return splitmix64(x + FIXED_RANDOM);
   }
};
#define prDouble(x) cout<<fixed<<setprecision(10)<<x
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using tll = tuple<ll,ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
const ll INF = 1e18, MOD = 1e9+7;

constexpr int md = 998244353;

template <typename T>
class Modular {
public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Modular() : value() {}

    template <typename U>
    Modular(const U& x) {
        value = normalize(x);
    }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod()) {
            v = static_cast<Type>(x);
        } else {
            v = static_cast<Type>(x % mod());
        }
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const {
        return value;
    }

    template <typename U>
    explicit operator U() const {
        return static_cast<U>(value);
    }

    constexpr static Type mod() {
        return T::value;
    }

    Modular& operator+=(const Modular& other) {
        if ((value += other.value) >= mod()) value -= mod();
        return *this;
    }

    Modular& operator-=(const Modular& other) {
        if ((value -= other.value) < 0) value += mod();
        return *this;
    }

    template <typename U>
    Modular& operator+=(const U& other) {
        return *this += Modular(other);
    }

    template <typename U>
    Modular& operator-=(const U& other) {
        return *this -= Modular(other);
    }

    Modular& operator++() {
        return *this += 1;
    }

    Modular& operator--() {
        return *this -= 1;
    }

    Modular operator++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }

    Modular operator--(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }

    Modular operator-() const {
        return Modular(-value);
    }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type&
    operator*=(const Modular& rhs) {
        value = normalize(1LL * value * rhs.value);
        return *this;
    }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type&
    operator*=(const Modular& rhs) {
        value = normalize(value * rhs.value);
        return *this;
    }

    friend Modular power(Modular a, long long e) {
        Modular r = 1;
        while (e > 0) {
            if (e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }

    friend Modular inverse(const Modular& a) {
        return power(a, mod() - 2);
    }

    Modular& operator/=(const Modular& other) {
        return *this *= inverse(other);
    }

    friend const Modular operator+(Modular lhs, const Modular& rhs) {
        return lhs += rhs;
    }

    friend const Modular operator-(Modular lhs, const Modular& rhs) {
        return lhs -= rhs;
    }

    friend const Modular operator*(Modular lhs, const Modular& rhs) {
        return lhs *= rhs;
    }

    friend const Modular operator/(Modular lhs, const Modular& rhs) {
        return lhs /= rhs;
    }

    friend bool operator==(const Modular& lhs, const Modular& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const Modular& lhs, const Modular& rhs) {
        return lhs.value != rhs.value;
    }

    friend ostream& operator<<(ostream& os, const Modular& number) {
        return os << number.value;
    }

    friend istream& operator>>(istream& is, Modular& number) {
        long long x;
        is >> x;
        number.value = normalize(x);
        return is;
    }

private:
    Type value;
};

using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int) fact.size() < n + 1) {
        fact.push_back(fact.back() * (int) fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
};

void solve() {
    cin >> n;
    string s;
    cin >> s;
    string t = ")((";
    vector<vector<vector<Mint>>> dp(4, vector(n + 1, vector(n + 1, Mint(0)))); // balance, length
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++){
        auto ndp = dp;
        int add = s[i] == '(' ? 1 : -1;
        for(int bal = 0; bal < n; bal++){
            for(int len = 0; len < n; len++){
                if(bal + add < 0) continue;
                for(int ii = 0; ii < 4; ii++){
                    int ni = ii;
                    if(ii == 0 and s[i] == ')') ni++;
                    if((ii == 1 or ii == 2) and s[i] == '(') ni++;
                    ndp[ni][bal + add][len + 1] += dp[ii][bal][len];
                }
            }
        }
        swap(dp, ndp);
    }

    Mint ans = 0;
    for(int i = 0; i <= n; i++){
        ans += dp[3][0][i] * (i - 2);
    }

    cout << ans << '\n';
}

int main() {
    fastio();
    cin >> t;
    while (t--) solve();
    return 0;
}

