#include<bits/stdc++.h>
using namespace std;

bool Solve(vector<int>& a, bool& got) {
    //int n = a.size();
    unordered_set<int> s(a.begin(),a.end());
    if(got) s.erase(-1);
    //empty nikla toh easily ho jayega kaam
    if(s.empty()) return true;

    int size = s.size();
    //Size lelia hai ab isko check karo

    if(size>1) return false;
    //final ans should be > 0
    return *s.begin()>0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>>n;
        vector<int> a(n);
        bool got = false;
        for(int i = 0; i < n; i++){
            cin>> a[i];
            if(a[i]==-1) got = true;
        }
        if(Solve(a,got)){
            cout<<"YES";
        } else {
            cout<<"NO";
        }
        cout<<endl;
    }
    return 0;
}