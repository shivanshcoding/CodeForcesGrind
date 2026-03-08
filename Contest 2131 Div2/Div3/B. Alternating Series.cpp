#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>>n;
        for(int i = 1; i <= n; i++){
            if(i%2==1){
                cout<<-1;
            }else{
                cout<<(i==n?2:3);
            }
            if(i<n){
                cout<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}
