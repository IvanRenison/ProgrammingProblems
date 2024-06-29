// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/L

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/** Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers x$ and y$, such that ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If a$ and b$ are coprime, then x$ is the inverse of a \pmod{b}$.
 */
ull euclid(ull a, ull b, ull &x, ull &y) {
  if (!b) return x = 1, y = 0, a;
  ull d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}

/** Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
const ull mod = 1e9 + 7; // change to something else
struct Mod {
  ull x;
  Mod(ull xx = 0) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    ull x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1); return Mod((x + mod) % mod);
  }
};

vector<Mod> fact(1001);

void init() {
  fact[0] = Mod(1);
  fore(i, 1, 1001) {
    fact[i] = fact[i - 1] * Mod(i);
  }
}

Mod solve(const vu& cs) {
  ull total = 0;
  Mod ans = 1;
  for (ull c : cs) {
    Mod this_ans = fact[c - 1 + total] / (fact[c - 1] * fact[total]);
    ans = ans * this_ans;
    total += c;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  init();

  ull k;
  cin >> k;
  vu cs(k);
  for (ull& c : cs) {
    cin >> c;
  }

  Mod ans = solve(cs);
  cout << ans.x << '\n';

}
