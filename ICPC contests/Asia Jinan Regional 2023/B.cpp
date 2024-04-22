// https://codeforces.com/gym/104901/problem/B

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif


//#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef tuple<uint, uint, uint> uuu;
typedef vector<uuu> vuuu;
typedef tuple<uint, uint, uint, uint> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<uint, uint, uint, uint, uint> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint inf = 1 << 30;

// Based on ModularArithmetic of kactl

constexpr ull mod = 998244353;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) >= mod ? x + b.x - mod : x + b.x);
  }
  Mod operator-(Mod b) const {
    return Mod(x >= b.x ? x - b.x : x + mod - b.x);
  }
  Mod operator*(Mod b) const {
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
  bool operator==(Mod b) const {
    return x == b.x;
  }
  bool operator!=(Mod b) const {
    return x != b.x;
  }
  bool operator<(Mod b) const {
    return x < b.x;
  }
  bool operator>(Mod b) const {
    return x > b.x;
  }
  bool operator<=(Mod b) const {
    return x <= b.x;
  }
  bool operator>=(Mod b) const {
    return x >= b.x;
  }

  Mod operator^(ull e) const {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    is >> m.x;
    return is;
  }

  operator ull() const {
    return x;
  }
  operator int() const {
    return x;
  }
};


typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;

Mod solveSmallK(uint k, const vector<vu>& adj) {
  uint n = adj.size();

  vector<vm> dp(n);

  function<void(uint, uint)> dfs = [&](uint u, uint p) {
    if (u != 0 && adj[u].size() == 1) {
      if (k == 1) {
        dp[u] = {1, 1};
      } else {
        dp[u] = {0, 1};
      }
    } else {
      dp[u] = {0, 1};

      for (uint v : adj[u]) {
        if (v != p) {
          dfs(v, u);
          vm new_dp(min((uint)(dp[v].size() + dp[u].size() + 1), k + 2));
          fore(s0, 0, dp[v].size()) {
            Mod v0 = dp[v][s0];
            fore(s1, 0, dp[u].size()) {
              Mod v1 = dp[u][s1];
              if (s0 + s1 <= k + 1 && v0 * v1 != Mod()) {
                new_dp[s0 + s1] += v0 * v1;
              }
            }
          }
          dp[u] = move(new_dp);

          dp[v].clear();
        }
      }

      Mod this_ans0 = 0;
      if (dp[u].size() > k) {
        this_ans0 = dp[u][k];
      }
      if (dp[u].size() > k + 1) {
        this_ans0 += dp[u][k + 1];
      }
      dp[u][0] = this_ans0;
    }
  };

  dfs(0, inf);

  return dp[0][k] + dp[0][k + 1];
}

Mod solveBigK(uint k, const vector<vu>& adj) {
  uint n = adj.size();

  vector<map<uint, Mod>> dp(n);

  function<void(uint, uint)> dfs = [&](uint u, uint p) {
    if (u != 0 && adj[u].size() == 1) {
      dp[u][1] = 1;
      if (k == 1) {
        dp[u][0] = 1;
      }
    } else {
      dp[u] = {{1, 1}};

      for (uint v : adj[u]) {
        if (v != p) {
          dfs(v, u);
          map<uint, Mod> new_dp;
          for (auto [s0, v0] : dp[v]) {
            for (auto [s1, v1] : dp[u]) {
              if (s0 + s1 <= k + 1 && v0 * v1 != Mod()) {
                new_dp[s0 + s1] += v0 * v1;
              }
            }
          }
          dp[u] = move(new_dp);

          dp[v].clear();
        }
      }

      Mod this_ans0 = 0;
      if (dp[u].count(k)) {
        this_ans0 = dp[u][k];
      }
      if (dp[u].count(k + 1)) {
        this_ans0 += dp[u][k + 1];
      }
      if (this_ans0 != Mod()) {
        dp[u][0] = this_ans0;
      }
    }
  };

  dfs(0, inf);

  return dp[0][k] + dp[0][k + 1];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n, k;
    cin >> n >> k;
    vector<vu> adj(n);
    fore(_, 0, n - 1) {
      uint u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v), adj[v].push_back(u);
    }

    auto ans = k*k > n ? solveBigK(k, adj) : solveSmallK(k, adj);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
