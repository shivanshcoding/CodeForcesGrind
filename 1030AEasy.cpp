#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool isHard = false;
    for (int i = 0; i < n; i++) {
        int opinion;
        cin >> opinion;
        if (opinion == 1) {
            isHard = true;
            break;
        }
    }

    cout << (isHard ? "HARD" : "EASY") << endl;
    return 0;
}

