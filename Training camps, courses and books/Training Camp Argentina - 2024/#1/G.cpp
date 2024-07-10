// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/G

#include <bits/stdc++.h>
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

/** Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers x$ and y$, such that ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If a$ and b$ are coprime, then x$ is the inverse of a \pmod{b}$.
 */
ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}

/** Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
const ll mod = 1e9 + 7;
struct Mod {
  ll x;
  Mod(ll xx = 0) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1); return Mod((x + mod) % mod);
  }
  Mod operator^(ll e) {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2); r = r * r;
    return e&1 ? *this * r : r;
  }
};

// Solve for p**e where p is prime
Mod solvePow(ll p, ll e, ll k) {

  vector<vector<Mod>> dp(e + 1, vector<Mod>(k + 1));
  vector<vector<Mod>> dp_sums(e + 2, vector<Mod>(k + 1));

  dp[0][0] = Mod(1);
  dp_sums[1][0] = Mod(1);
  fore(f, 1, e + 1) {
    dp[f][0] = dp[f - 1][0] * p;
    dp_sums[f + 1][0] = dp_sums[f][0] + dp[f][0];
  }

  fore(j, 1, k + 1) {
    dp[0][j] = Mod(1);
    dp_sums[1][j] = Mod(1);
    fore(f, 1, e + 1) {
      dp[f][j] = dp_sums[f + 1][j - 1] / Mod(f + 1);
      dp_sums[f + 1][j] = dp_sums[f][j] + dp[f][j];
    }
  }

  Mod ans = dp[e][k];

  return ans;
}

Mod solve(ll n, ll k) {
  vii fact;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ll e = 0;
      while (n % i == 0) {
        n /= i;
        e++;
      }
      fact.push_back({i, e});
    }
  }
  if (n > 1) {
    fact.push_back({n, 1});
  }

  Mod ans = Mod(1);

  for (auto [p, e] : fact) {
    ans = ans * solvePow(p, e, k);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll n, k;
  cin >> n >> k;
  Mod ans = solve(n, k);
  cout << ans.x << '\n';

}