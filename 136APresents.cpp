#include<bits/stdc++.h>
using namespace std;

void PrintSTL(const vector<int> & a) {
    for (const int i : a) {
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    int t;
    cin>> t;
    vector<int> v(t);
    for(int i=1;i<=t;i++){
        int ch;
        cin>>ch;
        v[ch-1] = i; 
    }
    PrintSTL(v);
    return 0;
}