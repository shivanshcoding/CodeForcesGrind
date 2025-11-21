#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ss second
#define ff first
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define gcd(a,b) __gcd(a,b);
#define cin(v) for(auto &i:v){cin>>i;}
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define nl "\n"
const int mod1=1e9+7;
const int mod=998244353;

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n);
    int even = 0;
    int e1 = -1, e2 = -1;
    for(int i=0; i<n; i++) {
        cin >> arr[i];

        if(arr[i] % 2 == 0) {
            even++;
            if(e1 == -1) {
                e1 = i;
            }
            else if(e2 == -1) {
                e2 = i;
            }
        }
    }

    if(even >= 2) {
        cout << arr[e1] << " " << arr[e2] << "\n";
        return;
    }

    if(n <= 1000) {
        for(int i=0; i<n-1; i++) {
            for(int j=i+1; j<n; j++) {
                if((arr[j] % arr[i]) % 2 == 0) {
                    cout << arr[i] << " " << arr[j] << "\n";
                    return;
                }
            }
        }

        cout << -1 << "\n";
    }
    else {
        for(int i=0; i<n-1; i++) {
            if((arr[i+1] % arr[i]) & 1 ^ 1) {
                cout << arr[i] << " " << arr[i + 1] << "\n";
                return;
            }
        }

        cout << -1 << "\n";
    }
    
}

int main() {

    fast

    // int t=1;

    int t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}