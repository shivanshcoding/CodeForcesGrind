// #include <bits/stdc++.h>
// using namespace std;
// struct custom_hash {
//    static uint64_t splitmix64(uint64_t x) {
//        x += 0x9e3779b97f4a7c15;
//        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//        return x ^ (x >> 31);
//    }
// size_t operator()(uint64_t x) const {
//        static const uint64_t FIXED_RANDOM =
//        chrono::steady_clock::now().time_since_epoch().count();
//        return splitmix64(x + FIXED_RANDOM);
//    }
// };
// #define prDouble(x) cout<<fixed<<setprecision(10)<<x
// #define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)
// #define all(x) (x).begin(), (x).end()
// #define rall(x) (x).rbegin(), (x).rend()
// #define pb push_back
// #define f first
// #define s second
// #define sz(x) (int)(x).size()
// using ll = long long;
// using ld = long double;
// using pll = pair<ll,ll>;
// using tll = tuple<ll,ll,ll>;
// using vll = vector<ll>;
// using vpll = vector<pll>;
// vector<ll> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1}; // for grid
// vector<ll> ddx = {1,1,0,-1,-1,-1,0,1}, ddy = {0,1,1,1,0,-1,-1,-1}; // 8 directions
// template<typename T> void read(vector<T> &v) { for (auto &x : v) cin >> x; }
// template<typename T> void printv(const vector<T>& v) { for (auto &x : v) cout << x << ' '; }
// template<typename T> void print2d(const vector<vector<T>>& v) { for (auto &row : v) { for (auto &x : row) cout << x << ' '; cout << '\n'; } }
// ll t=1,n,m,p,q,r,k,a,b,c,x,y,z;
// const ll INF = 1e18, MOD = 1e9+7;

// void solve() {
//     cin>>n;
//     vector<ll> a(n);
//     read(a);
//     sort(all(a));
//     unordered_set<ll> s;
//     bool flag = false;
//     for(int i=0;i<n;i++){
//         for(int j=2;j*j<=a[i];j++){
//             if(a[i]%j==0){
//                 if(s.find(j)!=s.end() or s.find(a[i]/j) !=s.end()){
//                     cout<<0<<"\n";
//                     return;
//                 }else{
//                     s.insert(j);
//                     s.insert(a[i]/j);
//                 }
//                 if(s.find(j-1)!=s.end() or s.find((a[i]/j)-1) !=s.end()){
//                     flag = true;
//                 }
//             }
//         }
//     }
//     if(flag) cout<<1<<"\n";
//     else cout<<2<<"\n";
// }

// int main() {
//     fastio();
//     cin >> t;
//     while (t--) solve();
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

// ------------------------------ PRIME UTILITIES ------------------------------
class PrimeUtils {
private:
    static const int LIMIT = 200005;
    vector<int> smallestPrime;
public:
    PrimeUtils() {
        smallestPrime.resize(LIMIT);
        generateSieve();
    }

    void generateSieve() {
        iota(smallestPrime.begin(), smallestPrime.end(), 0);
        for (int i = 2; i * i < LIMIT; ++i) {
            if (smallestPrime[i] == i) {
                for (int j = i * i; j < LIMIT; j += i) {
                    if (smallestPrime[j] == j)
                        smallestPrime[j] = i;
                }
            }
        }
    }

    // Extracts unique prime factors of n
    vector<int> getUniquePrimes(int n) const {
        vector<int> primes;
        if (n <= 1) return primes;
        while (n > 1) {
            int p = smallestPrime[n];
            primes.push_back(p);
            while (n > 1 && smallestPrime[n] == p)
                n /= p;
        }
        return primes;
    }
};

// ------------------------------ COST CALCULATOR ------------------------------
class CostFinder {
private:
    const PrimeUtils& primeTool;
    vector<bool> seenA, seenA1;
    vector<int> usedA, usedA1;

    void markFactors(const vector<int>& factors, vector<bool>& seen, vector<int>& used) {
        for (int p : factors) {
            if (!seen[p]) {
                seen[p] = true;
                used.push_back(p);
            }
        }
    }

    void reset(vector<int>& used, vector<bool>& seen) {
        for (int p : used) seen[p] = false;
        used.clear();
    }

public:
    CostFinder(const PrimeUtils& tool, int limit)
        : primeTool(tool), seenA(limit, false), seenA1(limit, false) {}

    int computeCost(const vector<int>& arr) {
        bool hasCost0 = false;

        // ---- COST 0 CHECK ----
        for (int x : arr) {
            auto factors = primeTool.getUniquePrimes(x);
            for (int p : factors) {
                if (seenA[p]) {
                    hasCost0 = true;
                    break;
                }
                seenA[p] = true;
                usedA.push_back(p);
            }
            if (hasCost0) break;
        }
        if (hasCost0) {
            cleanup();
            return 0;
        }

        // ---- COST 1 CHECK ----
        for (int x : arr) {
            auto nextFactors = primeTool.getUniquePrimes(x + 1);
            markFactors(nextFactors, seenA1, usedA1);
        }

        for (int p : usedA) {
            if (seenA1[p]) {
                cleanup();
                return 1;
            }
        }

        cleanup();
        return 2;
    }

    void cleanup() {
        reset(usedA, seenA);
        reset(usedA1, seenA1);
    }
};

// ------------------------------ DRIVER ------------------------------
class ProblemSolver {
private:
    PrimeUtils primes;
public:
    void process() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int t;
        cin >> t;

        CostFinder costFinder(primes, 200005);

        while (t--) {
            int n;
            cin >> n;
            vector<int> a(n), b(n);
            for (int i = 0; i < n; ++i) cin >> a[i];
            for (int i = 0; i < n; ++i) cin >> b[i]; // kept for structure; unused

            cout << costFinder.computeCost(a) << '\n';
        }
    }
};

// ------------------------------ MAIN ------------------------------
int main() {
    ProblemSolver().process();
    return 0;
}
