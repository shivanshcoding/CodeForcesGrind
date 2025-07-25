#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int odd=0,even=0;
        for(int i=0;i<n;i++){
            int ch;
            cin>>ch;
            if(ch%2==0){
                even++;
            }else{
                odd++;
            }
        }
        if(even>=1){
            cout<<1+odd<<endl;
        }else{
            cout<<max(0,odd-1)<<endl;
        }
    }
    return 0;
}
