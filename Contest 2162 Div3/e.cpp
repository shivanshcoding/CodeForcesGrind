// 5
// 4 1
// 1 3 3 4
// 4 2
// 2 2 2 2
// 5 1
// 4 1 5 2 2
// 6 3
// 1 2 3 4 5 6
// 5 3
// 3 2 5 2 3

// 2
// 1 3
// 3
// 3 4 1
// 4 1 5
// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     int t;
//     cin >> t;
//     const ll M = 1000000007LL;
//     const ll Q = 1000000009LL;
//     const ll B = 131;
//     const ll C = 137;
//     while (t--)
//     {
//         int n, k;
//         cin >> n >> k;
//         vector<int> a(n + 1);
//         for (int i = 1; i <= n; i++)
//             cin >> a[i];

//         vector<ll> x(n + 1, 1), y(n + 1, 0), u(n + 1, 1), v(n + 1, 0);
//         for (int i = 1; i <= n; i++)
//         {
//             x[i] = x[i - 1] * B % M;
//             y[i] = (y[i - 1] * B + a[i]) % M;
//             u[i] = u[i - 1] * C % Q;
//             v[i] = (v[i - 1] * C + a[i]) % Q;
//         }

//         auto g = [&](int l, int r) -> pair<ll, ll>
//         {
//             ll A = (y[r] - y[l - 1] * x[r - l + 1] % M + M) % M;
//             ll Bv = (v[r] - v[l - 1] * u[r - l + 1] % Q + Q) % Q;
//             return {A, Bv};
//         };

//         vector<int> b(n + 1);
//         for (int i = 1; i <= n; i++)
//             b[i] = a[n - i + 1];

//         vector<ll> w(n + 1, 0), z(n + 1, 0);
//         for (int i = 1; i <= n; i++)
//         {
//             w[i] = (w[i - 1] * B + b[i]) % M;
//             z[i] = (z[i - 1] * C + b[i]) % Q;
//         }

//         vector<int> c;
//         for (int r = 1; r <= n; r++)
//         {
//             auto h = g(n - r + 1, n);
//             ll r1 = w[r];
//             ll r2 = z[r];
//             if (h.first == r1 && h.second == r2)
//                 c.push_back(r);
//         }

//         vector<int> s;
//         int cur = n;
//         set<int> f;
//         f.insert(a[cur]);
//         for (int r : c)
//         {
//             if (r <= cur - 1)
//             {
//                 int p = cur - r;
//                 f.insert(a[p]);
//             }
//         }

//         int ch = 1;
//         while (ch <= n && f.count(ch))
//             ch++;

//         s.push_back(ch);
//         a.push_back(ch);
//         cur++;

//         if (k > 1)
//         {
//             int p1 = a[n];
//             int p2 = ch;
//             for (int i = 1; i < k; i++)
//             {
//                 int b1 = p1;
//                 int b2 = p2;
//                 ch = 1;
//                 while ((ch == b1 || ch == b2) && ch <= n)
//                     ch++;
//                 s.push_back(ch);
//                 p1 = p2;
//                 p2 = ch;
//             }
//         }

//         for (int i = 0; i < k; i++)
//         {
//             if (i)
//                 cout << " ";
//             cout << s[i];
//         }
//         cout << "\n";
//     }
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// -----------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------
namespace constants {
    const ll MOD_A = 1000000007LL;
    const ll MOD_B = 1000000009LL;
    const ll BASE_A = 131;
    const ll BASE_B = 137;
}

// -----------------------------------------------------------
// SMALL UTILS (used to change structure)
// -----------------------------------------------------------
namespace utils {
    template<typename T>
    void read_vec(vector<T>& v, int n) {
        for (int i = 1; i <= n; ++i) cin >> v[i];
    }

    template<typename T>
    vector<T> reversed(const vector<T>& v) {
        int n = (int)v.size() - 1;
        vector<T> r(n + 1);
        for (int i = 1; i <= n; ++i) r[i] = v[n - i + 1];
        return r;
    }

    template<typename S>
    int find_smallest_absent(S& st, int start = 1) {
        while (st.count(start)) ++start;
        return start;
    }
}

// -----------------------------------------------------------
// DOUBLE HASHER (restructured heavily)
// -----------------------------------------------------------
struct DoubleHash {
    vector<ll> pwr_a, pwr_b, pref_a, pref_b;
    ll base_a, base_b, mod_a, mod_b;
    int len;

    DoubleHash() = default;
    DoubleHash(const vector<int>& seq, ll ba, ll bb, ll ma, ll mb) {
        init(seq, ba, bb, ma, mb);
    }

    void init(const vector<int>& seq, ll ba, ll bb, ll ma, ll mb) {
        base_a = ba; base_b = bb; mod_a = ma; mod_b = mb;
        len = (int)seq.size() - 1;
        pwr_a.assign(len + 1, 1);
        pwr_b.assign(len + 1, 1);
        pref_a.assign(len + 1, 0);
        pref_b.assign(len + 1, 0);
        for (int i = 1; i <= len; ++i) {
            pwr_a[i] = (pwr_a[i - 1] * base_a) % mod_a;
            pwr_b[i] = (pwr_b[i - 1] * base_b) % mod_b;
            pref_a[i] = (pref_a[i - 1] * base_a + seq[i]) % mod_a;
            pref_b[i] = (pref_b[i - 1] * base_b + seq[i]) % mod_b;
        }
    }

    pair<ll, ll> sub_hash(int l, int r) const {
        ll h1 = (pref_a[r] - pref_a[l - 1] * pwr_a[r - l + 1] % mod_a + mod_a) % mod_a;
        ll h2 = (pref_b[r] - pref_b[l - 1] * pwr_b[r - l + 1] % mod_b + mod_b) % mod_b;
        return {h1, h2};
    }
};

// -----------------------------------------------------------
// SEQUENCE BUILDER CLASS
// -----------------------------------------------------------
struct SequenceBuilder {
    int n, k;
    vector<int> arr;
    set<int> used_values;
    vector<int> answer;
    DoubleHash forward_hash, backward_hash;

    SequenceBuilder(int n_, int k_, const vector<int>& a)
        : n(n_), k(k_), arr(a) {
        forward_hash = DoubleHash(arr, constants::BASE_A, constants::BASE_B, constants::MOD_A, constants::MOD_B);
        vector<int> rev = utils::reversed(arr);
        backward_hash = DoubleHash(rev, constants::BASE_A, constants::BASE_B, constants::MOD_A, constants::MOD_B);
    }

    vector<int> compute_palindrome_lengths() {
        vector<int> lens;
        for (int r = 1; r <= n; ++r) {
            auto h1 = forward_hash.sub_hash(n - r + 1, n);
            auto h2 = backward_hash.sub_hash(1, r);
            if (h1 == h2) lens.push_back(r);
        }
        return lens;
    }

    void fill_used_set(const vector<int>& lens) {
        used_values.insert(arr[n]);
        for (int len : lens) {
            if (len <= n - 1) {
                used_values.insert(arr[n - len]);
            }
        }
    }

    void generate_sequence() {
        auto lens = compute_palindrome_lengths();
        fill_used_set(lens);

        int new_val = utils::find_smallest_absent(used_values);
        arr.push_back(new_val);
        answer.push_back(new_val);

        if (k <= 1) return;

        int p1 = arr[n], p2 = new_val;
        for (int i = 1; i < k; ++i) {
            int nxt = 1;
            while ((nxt == p1 || nxt == p2) && nxt <= n) ++nxt;
            answer.push_back(nxt);
            p1 = p2;
            p2 = nxt;
        }
    }

    vector<int> get_result() {
        generate_sequence();
        return answer;
    }
};

// -----------------------------------------------------------
// SOLVER LOGIC
// -----------------------------------------------------------
struct Solver {
    void solve_one() {
        int n, k;
        cin >> n >> k;
        vector<int> a(n + 1);
        utils::read_vec(a, n);

        SequenceBuilder sb(n, k, a);
        vector<int> res = sb.get_result();

        for (int i = 0; i < (int)res.size(); ++i) {
            if (i) cout << " ";
            cout << res[i];
        }
        cout << "\n";
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t; cin >> t;
        while (t--) solve_one();
    }
};

// -----------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------
int main() {
    Solver().run();
    return 0;
}
