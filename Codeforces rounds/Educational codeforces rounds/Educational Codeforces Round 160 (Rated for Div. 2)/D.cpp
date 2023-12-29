// https://codeforces.com/contest/1913/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define sz(x) ((x).size())

const ull inf = 1ull << 60;

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = 998244353;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) {
    return Mod((x + mod - b.x + mod) % mod);
  }
  Mod operator*(Mod b) {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator-=(Mod b) {
    return *this = *this - b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
  }
  Mod operator--() {
    return *this = *this - Mod(1);
  }
  bool operator==(Mod b) {
    return x == b.x;
  }
  bool operator!=(Mod b) {
    return x != b.x;
  }
  bool operator<(Mod b) {
    return x < b.x;
  }
  bool operator>(Mod b) {
    return x > b.x;
  }
  bool operator<=(Mod b) {
    return x <= b.x;
  }
  bool operator>=(Mod b) {
    return x >= b.x;
  }

  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) {
    return *this * invert(b);
  }
  Mod operator/=(Mod b) {
    return *this = *this / b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    ull x;
    is >> x;
    m = Mod(x);
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

/** Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
struct RMQ {
  typedef ull T;
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      fore(j,0,sz(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

ull index_of_last_less(RMQ& t, ull x, ull r) {
  if (t.query(0, r) > x) {
    return r;
  }
  ull l = 0;
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (t.query(m, r) < x) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

Mod solve1(const vu& ps) {
  ull n = ps.size();

  RMQ rmq(ps);

  vector<vector<Mod>> dp(2, vector<Mod>(n));
  // dp[true][i] = Amount of posibilites until i keeping the i-th element
  // dp[false][i] = Amount of posibilites until i not keeping the i-th element

  vector<vector<Mod>> dp_sums(2, vector<Mod>(n + 1));

  dp[true][0] = 1;
  dp_sums[true][1] = 1;

  fore(i, 1, n) {
    ull j = index_of_last_less(rmq, ps[i], i);
    { // true
      ull l = j == i ? 0 : j;
      dp[true][i] += dp_sums[true][i] - dp_sums[true][l];
      dp[true][i] += dp[false][l];
      if (j == i) {
        dp[true][i] += Mod(1);
      }
    }
    { // false
      if (j < i) {
        dp[false][i] += dp[false][j] + dp[true][j];
      }
    }

    dp_sums[true][i + 1] = dp_sums[true][i] + dp[true][i];
    dp_sums[false][i + 1] = dp_sums[false][i] + dp[false][i];
  }

  return dp[false][n - 1] + dp[true][n - 1];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu ps(n);
    fore(j, 0, n) {
      cin >> ps[j];
    }

    auto ans = solve1(ps);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
