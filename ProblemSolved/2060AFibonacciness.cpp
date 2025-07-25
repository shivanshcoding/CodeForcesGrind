#include<bits/stdc++.h>
using namespace std;
vector<int> v(5);
int Count(){
    int count = 0;
    for(int i=0;i<3;i++){
        if(v[i+2]==v[i]+v[i+1]){
            count++;
        }
    }
    return count;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        for(int i=0;i<5;i++){
            if(i==2) continue;
            cin>>v[i];
        }
        v[2] = v[1]+v[0];
        int ans1 = Count();
        v[2] = v[3] - v[1];
        int ans2 = Count();
        cout<<max(ans1,ans2)<<endl;
    }
    return 0;
}
