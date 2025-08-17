/**
 *    author:  tourist
 *    created: 19.07.2025 09:08:47
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
struct TPoint {
  T x;
  T y;
  int id;

  TPoint() : x(0), y(0), id(-1) {}
  TPoint(const T& x_, const T& y_) : x(x_), y(y_), id(-1) {}
  TPoint(const T& x_, const T& y_, int id_) : x(x_), y(y_), id(id_) {}

  static constexpr T eps = static_cast<T>(1e-9);

  inline TPoint operator+(const TPoint& rhs) const { return TPoint(x + rhs.x, y + rhs.y); }
  inline TPoint operator-(const TPoint& rhs) const { return TPoint(x - rhs.x, y - rhs.y); }
  inline TPoint operator*(const T& rhs) const { return TPoint(x * rhs, y * rhs); }
  inline TPoint operator/(const T& rhs) const { return TPoint(x / rhs, y / rhs); }

  friend T smul(const TPoint& a, const TPoint& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend T vmul(const TPoint& a, const TPoint& b) {
    return a.x * b.y - a.y * b.x;
  }

  inline T abs2() const {
    return x * x + y * y;
  }

  inline bool operator<(const TPoint& rhs) const {
    return (y < rhs.y || (y == rhs.y && x < rhs.x));
  }

  inline bool is_upper() const {
    return (y > eps || (abs(y) <= eps && x > eps));
  }

  inline int cmp_polar(const TPoint& rhs) const {
    assert(abs(x) > eps || abs(y) > eps);
    assert(abs(rhs.x) > eps || abs(rhs.y) > eps);
    bool a = is_upper();
    bool b = rhs.is_upper();
    if (a != b) {
      return (a ? -1 : 1);
    }
    auto v = x * rhs.y - y * rhs.x;
    return (v > eps ? -1 : (v < -eps ? 1 : 0));
  }
};

using Point = TPoint<int>;
//using Point = TPoint<long double>;

template <typename T>
string to_string(const TPoint<T>& p) {
  return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<pair<int, int>> ps;
  while (n > 1) {
    vector<int> b;
    for (int i = 0; i < n; i += 2) {
      if (i < n - 1) {
        ps.emplace_back(a[i], a[i + 1]);
        b.push_back(a[i] + a[i + 1]);
      } else {
        b.push_back(a[i]);
      }
    }
    swap(a, b);
    n = int(a.size());
  }
  vector<Point> low = {{0, 0}};
  vector<Point> high = {{0, 1}};
  bool go_right = true;
  for (auto [u, v] : ps) {
    if (go_right) {
      for (int i = 0; i < u; i++) {
        auto lst = low.back();
        low.push_back({lst.x + 1, lst.y});
      }
      for (int i = 0; i < v; i++) {
        auto lst = high.back();
        high.push_back({lst.x + 1, lst.y});
      }
      int mx = max(high.back().x, low.back().x);
      high.back().x = low.back().x = mx;
      assert(high.back().y - low.back().y == 1);
      {
        auto lst = low.back();
        low.push_back({lst.x + 1, lst.y + 1000});
        low.push_back({lst.x, lst.y + 2001});
        high.push_back({lst.x, lst.y + 2000});
      }
    } else {
      for (int i = 0; i < u; i++) {
        auto lst = low.back();
        low.push_back({lst.x - 1, lst.y});
      }
      for (int i = 0; i < v; i++) {
        auto lst = high.back();
        high.push_back({lst.x - 1, lst.y});
      }
      int mn = min(high.back().x, low.back().x);
      high.back().x = low.back().x = mn;
      assert(high.back().y - low.back().y == 1);
      {
        auto lst = low.back();
        low.push_back({lst.x - 1, lst.y + 1000});
        low.push_back({lst.x, lst.y + 2001});
        high.push_back({lst.x, lst.y + 2000});
      }
    }
    go_right = !go_right;
    swap(low, high);
  }
  reverse(high.begin(), high.end());
  cout << low.size() + high.size() << '\n';
  for (auto& p : low) {
    cout << p.x << " " << p.y << '\n';
  }
  for (auto& p : high) {
    cout << p.x << " " << p.y << '\n';
  }
  return 0;
}
