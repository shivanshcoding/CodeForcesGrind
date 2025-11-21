#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
constexpr int mod = 1000000007;
// const int INF=LLONG_MAX>>1;
#define reverse(res) reverse(res.begin(), res.end());
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define umap unordered_map
#define uset unordered_set
#define pb push_back
#define eb emplace_back
#define pob pop_back
#define pii pair<int, int>
#define ff first
#define ss second
#define lb lower_bound
#define vi vector<int>
#define int long long
#define ub upper_bound
#define contain(map, i) (map.find(i) == map.end())
#define maxele max_element
#define minele min_element
#define len(s) (s).length()
#define nl cout << endl
#define rep(i, a, b) for (int i = a; i < b; i++)
#define trav(it, strt, end) for (auto it = strt; it != end; it++)
/*
**************************************************************************************************
**************************************************************************************************
***        **************
***        **************
***  ***   ***   ***
***  ***   ***   ***
***        ***
*************************
*************************
***        ***
***   ***   ***  ***
***   ***   ***  ***
**************        ***
**************        ***
*************************************************************************************************
**************************************************************************************************
*/
/*ll gcd(ll a ,ll b){
   if(b==0)return a;
   return gcd(b,a%b);
}
inttobin(int n){
string ans='';
while(n!=0){
    if(n%2==1)ans+='1';
    else ans+='0';
     n=n/2;
}
reverse(ans);
cout<<ans<<endl;
}
int bintodec(string s){
int n=s.size();
for(int i=n-1;i>=0;i--){
if(s[i]=='1')num+=pow(2,i);
}
return num;
}
long long fastExpo(int a, int b,int m ) {
long long  res = 1;
while(b > 0) {
if(b&1) {
res = (res)%m*(a)%m;
 }
b = b >> 1;
a = ((a)%m *( a)%m)%m;
 }
return res;
}
bool checkithsetbit(int n,int i){
return (n&(1<<i)!=0);
}
int setithbit(int n,int i){
return (n|(1<<i));
}
int clearithbit(int n,int i){
return(n&(~(1<<i)));
}
int toggleithbit(int n,int i){
return (n^(1<<i));
}
int addm(int a, int b)
{ return ((a % mod) + (b % mod)) % mod;}
int subtm(int a, int b)
{ return ((a % mod) - (b % mod) + mod) % mod;}
int mul(int a, int b)
{ return ((a % mod) * (b % mod)) % mod; }
int modInverse(int a)
{return fastpow(a, mod - 2);}
int divm(int a, int b)
{    return mul(a, modInverse(b));}
int fact(int n) {
int fact=1ll;
fact%=mod;
for(int i=1;i<=n;i++){
fact=((fact%mod)*(i%mod))%mod;
fact%=mod;
}
return fact%mod;
}*/
/************************************************/
/*for (int i = 2; i * i <= num; ++i) {
while (num % i == 0) {
count[i]++;
num /= i;
}
}
if (num > 1) {
count[num]++;
}*/
/************************************************/
/*const int N = 1e6;
vector<int> is_prime(N + 1, 1);
vector<int> primes;

void sieve() {
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}*/
/*int parent[N];
int size[N]; // Disjoint Set Union -> more at https://cp-algorithms.com/data_structures/disjoint_set_union.html

void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}

int find_set(int v) {
    if (parent[v] == v)
        return v;
    // Path compression
    return parent[v] = find_set(parent[v]);
}

void Union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        // Union by size
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}*/
/************************************************/
void debug(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        cerr << arr[i] << endl;
    }
    cerr << endl;
}
/************************************************/
void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<pair<int, int>> b(m);
    for (int i = 0; i < m; i++)
    {
        cin >> b[i].first;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i].second;
    }

    vector<pair<int, int>> d;
    vector<pair<int, int>> e;

    for (int i = 0; i < m; i++)
    {
        if (b[i].second == 0)
        {
            e.pb(b[i]);
        }
        else
        {
            d.pb(b[i]);
        }
    }

    sort(all(d));
    sort(all(e));

    multiset<int> mt;
    for (int i = 0; i < n; i++)
    {
        mt.insert(a[i]);
    }

    int kills = 0;

    for (int i = 0; i < d.size(); i++)
    {
        int h = d[i].first;
        int r = d[i].second;

        auto it = mt.lower_bound(h);

        if (it == mt.end())
        {
            break;
        }

        kills++;
        int k = *it;
        mt.erase(it);
        mt.insert(max(k, r));
    }

    vector<int> f;
    for (int sword : mt)
    {
        f.pb(sword);
    }

    int i = 0;
    int j = 0;

    while (i < e.size() && j < f.size())
    {
        int h = e[i].first;
        int k = f[j];

        if (k >= h)
        {
            kills++;
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }

    cout << kills << "\n";
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}