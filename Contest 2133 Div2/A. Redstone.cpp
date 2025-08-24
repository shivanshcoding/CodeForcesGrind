#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        bool ok = false;
        unordered_map<int,int> mpp;
        for(int i=0;i<n;i++){
            mpp[a[i]]++;
            if(mpp[a[i]]>=2){
                ok = true;
                break;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
