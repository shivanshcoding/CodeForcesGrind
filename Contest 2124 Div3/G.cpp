#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
const int P[2] = { 107, 61 };
int BP[2];

long long bin_pow(long long a, int n) {
    long long ret = 1;
    while (n) {
        if (n & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        n >>= 1;
    }
    return ret;
}

inline int add(int a, int b) {
    int res = a + b;
    if (res >= MOD) return res - MOD;
    return res;
}

inline int sub(int a, int b) {
    int res = a - b;
    if (res < 0) return res + MOD;
    return res;
}

inline int mult(int a, int b) {
    long long res = (long long)a * b;
    if (res >= MOD) return res % MOD;
    return res;
}

int main() {
    int t;
    cin >> t;
    
    BP[0] = bin_pow(P[0], MOD - 2);
    BP[1] = bin_pow(P[1], MOD - 2);
    vector <int> pows[2];
    vector <int> bpows[2];
    for (int j = 0; j < 2; j++) {
        pows[j].resize(1e6, 1);
        bpows[j].resize(1e6, 1);
        for (int i = 1; i < 1e6; i++) {
            pows[j][i] = mult(pows[j][i - 1], P[j]);
            bpows[j][i] = mult(bpows[j][i - 1], BP[j]);
        }
    }
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vector <string> f(n);
        for (int i = 0; i < n; i++)
            cin >> f[i];
        
        vector <vector <int>> hash(n + 2, vector <int> (m + 2, 0));
        vector <vector <int>> bhash(n + 2, vector <int> (m + 2, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int cur = mult((f[i - 1][j - 1] - 'a' + 1), mult(pows[0][i - 1], pows[1][j - 1]));
                hash[i][j] = add(sub(add(hash[i - 1][j], hash[i][j - 1]), hash[i - 1][j - 1]), cur);
            }
        }
        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                int cur = mult((f[i - 1][j - 1] - 'a' + 1), mult(pows[0][n - i], pows[1][m - j]));
                bhash[i][j] = add(sub(add(bhash[i + 1][j], bhash[i][j + 1]), bhash[i + 1][j + 1]), cur);
            }
        }
        
        auto isp = [&](int x1, int y1, int x2, int y2) {
            int hsh = add(sub(sub(hash[x2][y2], hash[x1-1][y2]), hash[x2][y1-1]), hash[x1-1][y1-1]);
            int bhsh = add(sub(sub(bhash[x1][y1], bhash[x2+1][y1]), bhash[x1][y2+1]), bhash[x2+1][y2+1]);
            hsh = mult(hsh, mult(bpows[0][x1 - 1], bpows[1][y1 - 1]));
            bhsh = mult(bhsh, mult(bpows[0][n - x2], bpows[1][m - y2]));
            return hsh == bhsh;
        };
        
        int mn = n * m * 4;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (isp(1, 1, i, j)) mn = min(mn, (2 * n - i) * (2 * m - j));
                if (isp(1, j, i, m)) mn = min(mn, (2 * n - i) * (m + j - 1));
                if (isp(i, 1, n, j)) mn = min(mn, (n + i - 1) * (2 * m - j));
                if (isp(i, j, n, m)) mn = min(mn, (n + i - 1) * (m + j - 1));
            }
        }
        
        cout << mn - m * n << '\n';
    }
    
    return 0;
}