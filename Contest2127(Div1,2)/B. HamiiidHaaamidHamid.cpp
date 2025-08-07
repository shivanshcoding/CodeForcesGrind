#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll,ll> ull;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl '\n'
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define F first
#define S second
#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define REPR(i, a, b) for (int i = (a); i > (b); --i)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define SORT(v) sort(all(v))
#define RSORT(v) sort(all(v), greater<int>())
#define REVERSE(v) reverse(all(v))
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define SQR(x) ((ll)(x) * (x))
#define RESET(a, b) memset(a, b, sizeof(a))
#define yes cout<<"YES"<<"\n"
#define no cout<<"NO"<<"\n"
#define input(a, n) for(int i = 0; i < n; i++) cin >> a[i]

const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LLINF = 1e18;
const double PI = acos(-1.0);
const double EPS = 1e-9;


ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll mod_add(ll a, ll b, ll m) { return (a % m + b % m) % m; }
ll mod_sub(ll a, ll b, ll m) { return (a % m - b % m + m) % m; }
ll mod_mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m; }
ll mod_pow(ll b, ll p, ll m) {
    ll r = 1;
    while (p) {
        if (p & 1) r = mod_mul(r, b, m);
        b = mod_mul(b, b, m);
        p >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        x--;

        cin.ignore();
        string s;
        getline(cin, s);

        int lcw = -1, rcw = n;
        for(int i=0;i<x;i++){
            if(s[i]=='#') lcw = i;
        }
        for(int i=x+1;i<n;i++){
            if(s[i]=='#'){
                rcw = i;
                break;
            }
        }
        int ans;
        if((lcw+1) > (n-rcw)){
            ans = min(lcw+1,n-1-x)+1;
        }else{
            ans = min(x,n-rcw)+1;
        }
        cout <<ans<< endl;
    }
    return 0;
}
