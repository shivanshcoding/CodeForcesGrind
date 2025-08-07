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

struct seg {
    ll start, end;
    
    seg(ll x, ll y) {
        start = min(x, y);
        end = max(x, y);
    }
    
    bool operator<(const seg& other) const {
        return start < other.start;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int n, k;
        cin >> n >> k; // k is not used
        
        vector<seg> segs;
        ll totalLength = 0;
        vector<ll> lefts(n), rights(n);
        
        for (int i = 0; i < n; i++) {
            cin >> lefts[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> rights[i];
        }
        
        for (int i = 0; i < n; i++) {
            segs.emplace_back(lefts[i], rights[i]);
            totalLength += segs[i].end - segs[i].start;
        }
        
        sort(segs.begin(), segs.end());
        
        bool hasOverlap = false;
        ll maxEnd = segs[0].end;
        ll minGap = LLONG_MAX;
        
        for (int i = 1; i < n; i++) {
            if (segs[i].start <= maxEnd) {
                hasOverlap = true;
                break;
            }
            minGap = min(minGap, segs[i].start - maxEnd);
            maxEnd = max(maxEnd, segs[i].end);
        }
        
        cout << (hasOverlap ? totalLength : totalLength + 2 * minGap) << "\n";
    }
    
    return 0;
}