#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i%2==0 or (i%4==1 and j==m-1) or (i%4==3 and j==0)){
                cout<<'#';
            }else{
                cout<<'.';
            }
        }
        cout<<endl;
    }
    return 0;
}