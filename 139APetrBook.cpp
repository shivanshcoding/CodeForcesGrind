#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>> n;
    vector<int> arr(7);
    for(int i=0;i<7;i++){
        cin>>arr[i];
    }
    int i = 0;
    while(n>0){
        n -= arr[i%7];
        i++;
    }
    cout<< (i - 1) % 7 + 1;
    return 0;
}