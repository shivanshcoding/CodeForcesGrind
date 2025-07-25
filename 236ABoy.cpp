#include<bits/stdc++.h>
using namespace std;

unordered_map<char,int> mpp;
int main(){
    string k;
    cin>>k;
    
    for(char c: k){
        mpp[c]++;
    }
    int n = mpp.size();
    if(n%2==0){
        cout<<"CHAT WITH HER!";
    }else{
        cout<<"IGNORE HIM!";
    }
    return 0;
}