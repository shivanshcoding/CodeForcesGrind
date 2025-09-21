#include <bits/stdc++.h>
using namespace std;

struct Node {
    int nxt[2];
    int sz;
    Node() { nxt[0] = nxt[1] = 0; sz = 0; }
};

struct BinaryTrie {
    static const int MAXB = 17;      // maximum bit length
    static const int MAXN = 4000010; // total nodes available
    vector<Node> pool;
    int root, tot;

    BinaryTrie() { pool.resize(MAXN); root = newNode(); }

    int newNode() {
        pool[tot] = Node();
        return tot++;
    }

    void clear() {
        tot = 0;
        root = newNode();
    }

    void add(int x) {
        int cur = root;
        pool[cur].sz++;
        for (int b = MAXB; b >= 0; --b) {
            int bit = (x >> b) & 1;
            if (!pool[cur].nxt[bit]) pool[cur].nxt[bit] = newNode();
            cur = pool[cur].nxt[bit];
            pool[cur].sz++;
        }
    }

    void remove(int x) {
        int cur = root;
        pool[cur].sz--;
        for (int b = MAXB; b >= 0; --b) {
            int bit = (x >> b) & 1;
            cur = pool[cur].nxt[bit];
            pool[cur].sz--;
        }
    }

    int bestMatch(int mask) {
        if (pool[root].sz == 0) return -1;
        int cur = root, val = 0;
        for (int b = MAXB; b >= 0; --b) {
            int mb = (mask >> b) & 1;
            int choice = -1;
            if (mb == 0) {
                if (pool[cur].nxt[1] && pool[pool[cur].nxt[1]].sz > 0) choice = 1;
                else if (pool[cur].nxt[0] && pool[pool[cur].nxt[0]].sz > 0) choice = 0;
            } else {
                if (pool[cur].nxt[0] && pool[pool[cur].nxt[0]].sz > 0) choice = 0;
            }
            if (choice == -1) return -1;
            if (choice) val |= (1 << b);
            cur = pool[cur].nxt[choice];
        }
        return val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    BinaryTrie trie;

    while (T--) {
        int L, R;
        cin >> L >> R;

        long long sum_or = 1LL * R * (R + 1);
        cout << sum_or << "\n";

        trie.clear();
        for (int x = L; x <= R; ++x) trie.add(x);

        int len = R - L + 1;
        vector<int> out;
        out.reserve(len);

        for (int i = 0; i < len; i++) {
            int pos = L + i;
            int val = trie.bestMatch(pos);
            out.push_back(val);
            trie.remove(val);
        }

        for (int i = 0; i < len; i++) {
            cout << out[i] << (i + 1 == len ? '\n' : ' ');
        }
    }
    return 0;
}
