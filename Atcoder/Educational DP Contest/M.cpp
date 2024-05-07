// https://atcoder.jp/contests/dp/tasks/dp_m

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = (1e9 + 7);
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

struct presums {
  typedef Mod T;
  T op(T a, T b) { return a + b; }
  T rev(T a, T b) { return a - b; }
  const T neut = 0;
  // rev(op(a, b), b) = a

  ull n;
  vector<T> as;

  presums(ull n) : n(n), as(n + 1) {}

  void update(ull i, ull j, T v) { // [i, j)
    as[i] = op(as[i], v);
    as[j] = rev(as[j], v);
  }

  vector<T> build() {
    vector<T> ans(n);
    ans[0] = as[0];
    fore(i, 1, n) {
      ans[i] = op(ans[i - 1], as[i]);
    }
    return ans;
  }
};


Mod solve(ull K, vector<ull> as) {
  ull N = as.size();

  vector<Mod> dp(K+1);
  fore(a, 0, as[0] + 1) {
    dp[a] = 1;
  }

  fore(i, 1, N) {
    presums dp_next(K+1);

    fore(k, 0, K + 1) {
      dp_next.update(k, min(K+1, k + as[i] + 1), dp[k]);
    }

    dp = dp_next.build();
  }

  return dp[K];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, K;
  cin >> N >> K;
  vector<ull> as(N);
  for(ull& a : as) {
    cin >> a;
  }

  cout << solve(K, as) << '\n';

  return EXIT_SUCCESS;
}
