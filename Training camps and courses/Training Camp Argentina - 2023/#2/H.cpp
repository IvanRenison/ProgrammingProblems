// https://codeforces.com/group/hzSLIARNBN/contest/465113/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

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

Mod solve(vector<pair<ull, ull>> edges) {
  ull n = edges.size() + 1;

  vector<vector<ull>> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<vector<Mod>> dp(n, vector<Mod>(2, 0));
  vector<vector<bool>> dp_valid(n, vector<bool>(2, false));
  // dp[u][0] = Amount in subtree of u without using u
  // dp[u][1] = Amount in subtree of u using u

  function<Mod(ull, bool, ull)> f = [&](ull u, bool use, ull p) {
    if (dp_valid[u][use]) {
      return dp[u][use];
    }
    Mod ans;
    if ((u == p && adj[u].empty()) || (u != p && adj[u].size() == 1)) {
      if (use) {
        ans = 0;
      } else {
        ans = 1;
      }
    } else if (use) {
      Mod prod_rec = 1;
      for (auto v : adj[u]) {
        if (v != p) {
          prod_rec *= f(v, true, u) * Mod(2) + f(v, false, u);
        }
      }
      ans = 0;
      for (auto v : adj[u]) {
        if (v != p) {
          Mod this_rec = f(v, true, u) * Mod(2) + f(v, false, u);
          Mod this_ans = prod_rec / this_rec;
          for (auto w : adj[v]) {
            if (w != u) {
              this_ans *= f(w, true, v) * Mod(2) + f(w, false, v);
            }
          }
          ans += this_ans;
        }
      }
    } else {
      ans = 1;
      for (auto v : adj[u]) {
        if (v != p) {
          ans *= f(v, false, u) + f(v, true, u);
        }
      }
    }

    dp_valid[u][use] = true;
    dp[u][use] = ans;
    return ans;
  };

  Mod ans = f(0, false, 0) + f(0, true, 0);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<pair<ull, ull>> edges(n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  auto ans = solve(edges);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
