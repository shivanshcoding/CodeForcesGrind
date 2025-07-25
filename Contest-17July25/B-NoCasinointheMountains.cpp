#include<bits/stdc++.h>
using namespace std;

int Ans(int n, int k, const vector<int>& arr){
    vector<int> nOne(n);
    int nextOne = n;
    int ans = 0;
    for(int i=n-1;i>=0;i--){
        if(arr[i]==1) nextOne = i;
        else{
            nOne[i] = nextOne;
        }
    }
    for(int i=0;i<(n+1-k);i++){
        if(nOne[i] > i+k-1){
            ans++;
            i = i+k;
        }
    }
    return ans;
}

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n, k;
        cin>>n>>k;
        vector<int> arr(n);
        for(int i=0;i<n;i++) cin>>arr[i];
        cout<<Ans(n,k,arr);
        cout<<endl;
    }
    return 0;
}