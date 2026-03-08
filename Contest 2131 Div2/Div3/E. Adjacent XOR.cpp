#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

// yeh function check karega ki array a ko b me convert kiya ja sakta hai ya nahi
bool solve(vector<int> &a, vector<int> &b) {
    // last element kabhi change nahi ho sakta, to equal hona chahiye
    if (a[n - 1] != b[n - 1]) {
        return false;
    }

    bool ok = true;

    // right se left traverse karenge (n-2 se 0 tak)
    for (int i = n - 2; i >= 0; --i) {
        ll want = b[i];      // b[i] me hume final value chahiye
        ll orig = a[i];      // original value a[i]

        // Teen possible values jo a[i] ban sakta hai:
        ll c1 = orig;                  // case 1: koi operation nahi kiya
        ll c2 = orig ^ a[i + 1];        // case 2: operation yaha kiya (a[i] ^ a[i+1] original values se)
        ll c3 = orig ^ b[i + 1];        // case 3: operation yaha kiya lekin a[i+1] ab b[i+1] ban chuka hai

        // agar chahiye value kisi bhi case me mil gayi to ok
        if (want == c1 || want == c2 || want == c3) {
            continue; // next index check karo
        } else {
            ok = false;
            break;
        }
    }
    return ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        cin >> n;
        vector<int> a(n), b(n);

        // array a input
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        // array b input
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        // agar possible hai to YES print karo warna NO
        if (solve(a, b))
            cout << "YES";
        else
            cout << "NO";
        cout << '\n';
    }
    return 0;
}
