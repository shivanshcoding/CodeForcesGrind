#include<bits/stdc++.h>
using namespace std;

int solve(int n, int k, vector<int>& a, vector<int>& b) {
    int match = -1;
    for(int i = 0; i < n; i++) {
        if(b[i] != -1) {
            if(match == -1 || b[i] + a[i] == match) {
                match = b[i] + a[i];
            } else {
                return 0;
            }
        }
    }
    if(match == -1) {
        return *min_element(a.begin(), a.end()) + k - *max_element(a.begin(), a.end()) + 1;
    }else{
        for(int i=0;i<n;i++){
            if(b[i] == -1) {
                if(match < a[i] || match > k + a[i]) {
                    return 0;
                }
            }
        }
        return 1;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> b(n);
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        cout<<solve(n,k,a,b)<<endl;
    }
    return 0;
}