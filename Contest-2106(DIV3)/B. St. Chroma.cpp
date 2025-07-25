#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vector<int> res;

        for(int i=0;i<n;i++){
            if(i!=x) cout<<i<<" ";
        }
        if(x<n) cout<<x;
        cout << '\n';
    }
    return 0;
}
