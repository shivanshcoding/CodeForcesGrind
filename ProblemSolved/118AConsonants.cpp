#include<bits/stdc++.h>
using namespace std;

unordered_set<char> s =  {'a','o','y','e','u','i'};
int main(){
    string k;
    cin>>k;
    string ans;
    for(char c: k){
        if(c<97){
            c = c+32;
        }
        if(s.find(c)==s.end()){
            ans.push_back('.');
            ans.push_back(c);
        }
    }
    cout<<ans;
    return 0;
}