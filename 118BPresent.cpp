#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    for (int i = 0; i < 2*n+1; i++) {
        for(int j = 0; j < abs(n-i); j++){ 
            cout<<"  ";
        }
        int m = min(i,2*n-i);
        for(int j=0; j<2*m+1;j++) {
            if(j!=0) cout<<" ";
            cout<<min(j,2*m-j);
        }
        cout<<endl;
    }
    return 0;
}