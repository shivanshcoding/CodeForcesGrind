#include <iostream>
using namespace std;

int cnt1[26], cnt2[26];
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        for (int i = 0; i < 26; ++i) cnt1[i] = cnt2[i] = 0;
        int n;
        cin >> n;
        string s, t;
        cin >> s >> t;
        for (char &c : s) cnt1[c - 'a'] ++;
        for (char &c : t) cnt2[c - 'a'] ++;
        bool answer = true;
        for (int i = 0; i < 26; ++i)
            if (cnt1[i] != cnt2[i]) 
                answer = false;
        puts(answer ? "YES" : "NO");
    }
}