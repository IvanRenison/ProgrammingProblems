// https://codeforces.com/contest/1794/problem/D

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

constexpr ull mod = 998244353ull;
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

#define MAXA ull(1e6 + 1)

Mod facts[MAXA];

void init() {
  facts[0] = 1;
  fore(i, 1, MAXA) {
    facts[i] = facts[i - 1] * Mod(i);
  }
}

bool is_prime(ull n) {
  if (n <= 1) {
    return false;
  }
  if (n <= 3) {
    return true;
  }
  if (n % 3 == 0 || n % 2 == 0) {
    return false;
  }
  for (ull i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

Mod solve(vector<ull> as) {
  ull n = as.size() / 2;
  map<ull, ull> primes, non_primes;

  for (ull a : as) {
    if (is_prime(a)) {
      primes[a]++;
    } else {
      non_primes[a]++;
    }
  }

  vector<ull> primes_vec, non_primes_vec;
  for (auto [p, c] : primes) {
    primes_vec.push_back(c);
  }
  for (auto [x, c] : non_primes) {
    non_primes_vec.push_back(c);
  }

  ull primes_count = primes_vec.size(),
      non_primes_count = non_primes_vec.size();

  if (primes_count < n) {
    return 0;
  }

  Mod base_value = facts[n];
  fore(i, 0, non_primes_count) {
    base_value /= facts[non_primes_vec[i]];
  }

  vector<vector<Mod>> dp(primes_count + 1, vector<Mod>(n + 1));
  // dp[i][j] = Amount with j primes between the first i primes

  dp[0][0] = base_value;
  fore(i, 1, primes_count + 1) {
    dp[i][0] = dp[i - 1][0] / facts[primes_vec[i - 1]];
    fore(j, 1, min(i + 1, n + 1)) {
      dp[i][j] = dp[i - 1][j] / facts[primes_vec[i - 1]] +
                 dp[i - 1][j - 1] / facts[primes_vec[i - 1] - 1];
    }
  }

  Mod ans = dp[primes_count][n];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  init();

  ull n;
  cin >> n;
  vector<ull> as(2 * n);
  fore(i, 0, 2 * n) {
    cin >> as[i];
  }

  cout << solve(as) << '\n';

  return EXIT_SUCCESS;
}
