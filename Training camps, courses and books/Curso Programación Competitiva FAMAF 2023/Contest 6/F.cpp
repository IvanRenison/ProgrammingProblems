// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;
  vector<ull> as(n);
  for (ull& a : as) {
    cin >> a;
  }

  return as;
}

struct Tree {
  typedef optional<ull> T;
  static constexpr T unit = {};
  T f(T a, T b) {
    if (!a.has_value()) {
      return b;
    } else if (!b.has_value()) {
      return a;
    }
    return gcd(a.value(), b.value());
  } // (any associative fn)
  vector<T> s;
  ll n;
  Tree(ll n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = f(ra, s[b++]);
      if (e % 2)
        rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

ull solve1(vector<ull>& as) {
  ull n = as.size();
  Tree t(n - 1);

  fore(i, 1, n) {
    t.update(i - 1, max(as[i], as[i - 1]) - min(as[i], as[i - 1]));
  }

  ull s = 0, e = 1;
  ull ans = 0;

  while (e < n) {
    if (e <= s || t.query(s, e).value() > 1) {
      ans = max(ans, e - s);
      e++;
    } else {
      s++;
    }
  }

  return ans + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
