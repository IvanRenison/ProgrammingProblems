#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

#define MAXA 300

/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
  typedef ull T;
  static constexpr T unit = 0;
  T f(T a, T b) {
    return max(a, b);
  } // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
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

ull solve(vector<ull> as, ull T) {
  ull n = as.size();

  Tree dp(MAXA);

  ull ans = 0;

  fore(i, 0, min(n, T)) {
    fore(j, 0, n) {
      ull a = as[j];
      ull this_ans = dp.query(0, a + 1) + 1;
      dp.update(a, this_ans);
      ans = max(ans, this_ans);
    }
  }

  if (T > n) {
    vector<ull> amounts(MAXA);
    for (ull a : as) {
      amounts[a]++;
    }

    ull max_amount = 0;
    for (ull amount : amounts) {
      max_amount = max(max_amount, amount);
    }

    ans += (T - n) * max_amount;
  }

  return ans;
}

int main() {
  FIN;

  ull n, T;
  cin >> n >> T;
  vector<ull> as(n);
  for (ull& a : as) {
    cin >> a;
    a--;
  };

  cout << solve(as, T) << '\n';

  return 0;
}
