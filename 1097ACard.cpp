#include <bits/stdc++.h>
using namespace std;

int main() {
    string tableCard;
    cin >> tableCard;

    bool canPlay = false;
    for (int i = 0; i < 5; i++) {
        string handCard;
        cin >> handCard;
        if (handCard[0] == tableCard[0] || handCard[1] == tableCard[1]) {
            canPlay = true;
        }
    }

    cout << (canPlay ? "YES" : "NO") << endl;
    return 0;
}
